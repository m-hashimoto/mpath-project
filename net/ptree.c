/* Patricia-like Tree */
#include "opt_ptree.h"

#ifdef _KERNEL
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/syslog.h>
#include <net/ptree.h>
#else /*_KERNEL*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/types.h>
#include <assert.h>
#endif /*_KERNEL*/

char mask[] = { 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };

static struct ptree_node *
ptree_node_create (char *key, int keylen)
{
  struct ptree_node *x;
  int len;

  len = sizeof (struct ptree_node) + keylen / 8 + 1;

  XRTMALLOC(x, struct ptree_node *, len);
  if (! x)
    return NULL;

  x->key = (char *)((caddr_t)x + sizeof (struct ptree_node));
  x->keylen = keylen;
  x->parent = NULL;
  x->child[0] = NULL;
  x->child[1] = NULL;
  x->data = NULL;

  /* fill in the key */
  memcpy (x->key, key, keylen);
  x->key[keylen / 8] = key[keylen / 8] & mask[keylen % 8];

  return x;
}

static void
ptree_node_delete (struct ptree_node *x)
{
  XRTFREE (x);
}

/* check_bit() returns the "keylen"-th bit in the key.
   key[keylen] would return the bit just after the key,
   because the index of the key[] starts with 0-origin. */
static int
check_bit (char *key, int keylen)
{
  int offset;
  int shift;

  offset = keylen / 8;
  shift = 7 - keylen % 8;

  return (key[offset] >> shift & 1);
}

/* ptree_match() returns 1 iff keyi and keyj are the same
   in keylen bits */
static int
ptree_match (char *keyi, char *keyj, int keylen)
{
#ifdef DEBUG
printf("ptree_match\n");
printf("keyi: %p, keyj: %p, keylen: %d\n",keyi,keyj,keylen);
#endif
  int bytes;
  int bits;
  bytes = (int)keylen / 8;
  bits = (int)keylen % 8;
#ifdef DEBUG
printf("bytes: %d, bits %d\n",bytes,bits);
printf("keyi[bytes] = %d, keyj[bytes] = %d\n",keyi[bytes],keyj[bytes]);
#endif
  if (! memcmp (keyi, keyj, bytes) &&
      ! (keyi[bytes] ^ keyj[bytes]) & mask[bits])
    return 1;
  return 0;
}

/* ptree_lookup() returns the node with the key if any.
   returned node may be a branching node (that doesn't have data). */
struct ptree_node *
ptree_lookup (void *key, void *mask, int keylen, struct ptree *t)
{
  struct ptree_node *x;
  caddr_t netmask = 0;

  if (mask) {
	  x = ptree_addmask(mask, 1, t->rnh_treetop->rn_offset);
	  if (x == 0)
		  return (0);
	  netmask = x->rn_key;
  }

  x = t->top;
  while (x && x->keylen <= keylen &&
		  ptree_match (x->key, key, x->keylen))
	  x = x->child[check_bit (key, x->keylen)];
  if (x->keylen == keylen)
	  return x;

  return NULL;
}

/* ptree_search() returns the ptree_node with data
   that matches the key. If data is NULL, it is a branching node,
   and ptree_search() ignores it. no caller reference lock. */
#if 0
	struct ptree_node *
ptree_search (char *key, int keylen, struct ptree *t)
{
#ifdef DEBUG
printf("ptree_search\n");
printf("key = %p, keylen = %d, ptree = %p\n",&key,keylen,t);
#endif
	struct ptree_node *x, *match;

	match = NULL;
	x = t->top;
#ifdef DEBUG
	printf("ptree_search: treetop->key = %p\n",x->key);
	printf("ptree_search: treetop->keylen = %d\n",x->keylen);
#endif
	while (x && x->keylen <= keylen &&
			ptree_match (x->key, key, x->keylen))
	{
		if (x->data)
			match = x;
		x = x->child[check_bit (key, x->keylen)];
#ifdef DEBUG
printf("ptree_seach: child->key = %p, keylen = %d\n",x->key.x->keylen);
#endif

	}

	return match;
}
#endif
	struct ptree_node *
ptree_search(key, keylen, t)
	char *key;
	int keylen;
	struct ptree *t;
{
#ifdef DEBUG
printf("ptree_search\n");
printf("key = %p, keylen = %d, ptree = %p\n",key,keylen,t);
#endif
	register struct ptree_node *x;
	register caddr_t v;

	for (x = t->top, v = key; x->keylen <= keylen && x->rn_bit >= 0;) {
#ifdef DEBUG
printf("ptree_search: x->rn_bit = %d, x->rn_offset = %d\n",x->rn_bit,x->rn_offset);
#endif
		if (x->rn_bmask & v[x->rn_offset]){
			x = x->rn_right;
#ifdef DEBUG
printf("go to right node\n");
printf("ptree_search: x->rn_right = %p, keylen = %d\n",x->key,x->keylen);
#endif
		}
		else{
			x = x->rn_left;
#ifdef DEBUG
printf("go to left node\n");
printf("ptree_search: x->rn_left = %p, keylen = %d\n",x->key,x->keylen);
#endif
		}
	}
#ifdef DEBUG
printf("return node\n");
printf("ptree_search: x = %p, keylen = %d\n",x->key,x->keylen);
#endif
	return (x);
}

	static void
ptree_link (struct ptree_node *v, struct ptree_node *w)
{
	/* check the w's key bit just after the v->key (keylen'th bit) */
	int bit;

	bit = check_bit (w->key, v->keylen);
	v->child[bit] = w;
	w->parent = v;
}

/* key_common_len() returns the bit length with which the keyi and
   the keyj are equal */
	static int
key_common_len (char *keyi, int keyilen, char *keyj, int keyjlen)
{
	int i;
	int nmatch = 0;
	int minkeylen = MIN (keyilen, keyjlen);
	int keylen = 0;
	unsigned char bitmask;
	unsigned char diff;

	for (i = 0; i < minkeylen / 8; i++)
	{
		if (keyi[i] == keyj[i])
			nmatch = i + 1;
	}

	keylen = nmatch * 8;
	bitmask = 0x80;
	diff = keyi[nmatch] ^ keyj[nmatch];
	while (keylen < minkeylen && ! (bitmask & diff))
	{
		keylen++;
		bitmask >>= 1;
	}

	return keylen;
}

/* ptree_common() creates and returns the branching node
   between keyi and keyj */
	static struct ptree_node *
ptree_common (char *keyi, int keyilen, char *keyj, int keyjlen)
{
	int keylen;
	struct ptree_node *x;

	keylen = key_common_len (keyi, keyilen, keyj, keyjlen);
	x = ptree_node_create (keyi, keylen);
	if (! x)
		return NULL;

	return x;
}

/* locks the node */
#if 0
   void
   ptree_node_lock (struct ptree_node *x)
   {
   x->lock++;
   }
 
/* unlocks the node. if the lock(reference) becomes 0,
   it will be removed. */

   void
   ptree_node_unlock (struct ptree_node *x)
   {
   x->lock--;
   if (x->lock == 0)
   ptree_remove (x);
   }
#endif

/* locks for the tree holding
   but does not lock for the caller reference. */
	static struct ptree_node *
ptree_get (char *key, int keylen, struct ptree *t)
{
	struct ptree_node *x;
	struct ptree_node *u, *v, *w; /* u->v->w or u->x->{v, w}*/

	u = w = NULL;
	x = t->top;
	while (x && x->keylen <= keylen &&
			ptree_match (x->key, key, x->keylen))
	{
		if (x->keylen == keylen)
			return x;
		u = x;
		x = x->child[check_bit (key, x->keylen)];
	}

	if (! x)
	{
		v = ptree_node_create (key, keylen);
		if (u)
			ptree_link (u, v);
		else
			t->top = v;
	}
	else
	{
		/* we're going to insert between u and w (previously x) */
		w = x;

		/* create branching node */
		x = ptree_common (key, keylen, w->key, w->keylen);
		if (! x)
		{
			XRTLOG (LOG_ERR, "ptree_get(%p,%d): "
					"ptree_common() failed.\n", key, keylen);
			return NULL;
		}

		/* set lower link */
		ptree_link (x, w);

		/* set upper link */
		if (u)
			ptree_link (u, x);
		else
			t->top = x;

		/* if the branching node is not the corresponding node,
		   create the corresponding node to add */
		if (x->keylen == keylen)
			v = x;
		else
		{
			v = ptree_node_create (key, keylen);
			if (! v)
			{
				XRTLOG (LOG_ERR, "ptree_get(%p,%d): "
						"ptree_common() failed.\n", key, keylen);
				return NULL;
			}

			ptree_link (x, v);
		}
	}
	return v;
}

	struct ptree_node *
ptree_add (char *key, int keylen, void *data, struct ptree *t)
{
	struct ptree_node *x;

	x = ptree_get (key, keylen, t);
	if (! x)
	{
		XRTLOG (LOG_ERR, "ptree_add(%p,%d): "
				"ptree_get() failed.\n", key, keylen);
		return NULL;
	}

	x->data = data;

	return x;
}

	void
ptree_remove (struct ptree_node *v)
{
	struct ptree_node *w;

	XRTASSERT (! v->data, ("ptree: attempt to remove a node with data"));

	/* do not remove if the node is the branching node */
	if (v->child[0] && v->child[1])
		return;

	/* if a stub node */
	if (! v->child[0] && ! v->child[1])
	{
		if (v->parent->child[0] == v)
			v->parent->child[0] = NULL;
		else
			v->parent->child[1] = NULL;
		ptree_node_delete (v);
		return;
	}

	w = (v->child[0] ? v->child[0] : v->child[1]);
	ptree_link (v->parent, w);
	ptree_node_delete (v);
}

	struct ptree_node *
ptree_head (struct ptree *t)
{
	if (! t->top)
		return NULL;

	return t->top;
}

	struct ptree_node *
ptree_next (struct ptree_node *v)
{
	struct ptree_node *t;
	struct ptree_node *u;
	struct ptree_node *w;

	/* if the left child exists, go left */
	if (v->child[0])
	{
		w = v->child[0];
		return w;
	}

	if (v->child[1])
	{
		w = v->child[1];
		return w;
	}

	u = v->parent;

	if (u->child[0] == v)
	{
		w = u->child[1];
		return w;
	}

	t = u->parent;
	while (t && (t->child[1] == u || ! t->child[1]))
	{
		u = t;
		t = t->parent;
	}

	if (t)
	{
		/* return the not-yet-traversed right-child node */
		w = t->child[1];
		XRTASSERT (w, ("xrt: an impossible end of traverse"));

		return w;
	}

	/* end of traverse */
	return NULL;
}

	struct ptree *
ptree_create ()
{
	struct ptree *t;

	XRTMALLOC(t, struct ptree *, sizeof (struct ptree));
	if (! t)
		return NULL;

	t->top = NULL;
	return t;
}

	void
ptree_delete (struct ptree *t)
{
	struct ptree_node *x;

	for (x = ptree_head (t); x; x = ptree_next (x))
		ptree_node_delete (x);

	XRTFREE (t);
}