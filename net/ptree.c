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

#define dprint(x) { if(DEBUG) printf x; }

char mask[] = { 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };

	static struct ptree_node *
ptree_node_create (char *key, int keylen)
{
	dprint(("ptree_node_create Start\n"));
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

	x->rn_bit = keylen;
	x->rn_bmask = 0x80 >> (keylen & 7);
	x->rn_offset = keylen >> 3;
	x->rn_flags = RNF_ACTIVE;
	x->rn_mklist = 0;
#ifdef PTREE_MPATH
	x->mpath_array = 0;
#endif

	dprint(("ptree_node_create End\n"));
	return x;
}

	static void
ptree_node_delete (struct ptree_node *x)
{
	dprint(("ptree_node_delete Start\n"));
	XRTFREE (x);
	dprint(("ptree_node_delete End\n"));
}

/* check_bit() returns the "keylen"-th bit in the key.
   key[keylen] would return the bit just after the key,
   because the index of the key[] starts with 0-origin. */
	static int
check_bit (char *key, int keylen)
{
	dprint(("check_bit Start\n"));
	int offset;
	int shift;

	offset = keylen / 8;
	shift = 7 - keylen % 8;

	dprint(("check_bit End\n"));
	return (key[offset] >> shift & 1);
}

/* ptree_match() returns 1 iff keyi and keyj are the same
   in keylen bits */
	static int
ptree_match (char *keyi, char *keyj, int keylen)
{
	dprint(("ptree_match Start\n"));
	int bytes;
	int bits;
	bytes = (int)keylen / 8;
	bits = (int)keylen % 8;

	dprint(("ptree_match End\n"));
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
	dprint(("ptree_lookup Start\n"));
	struct ptree_node *x;
	caddr_t netmask = 0;

	if (mask) {
		x = ptree_addmask(mask, 1, t->top->rn_offset);
		if (x == 0)
			return (0);
		netmask = x->rn_key;
	}

	x = t->top;
	while (x && x->keylen <= keylen &&
			ptree_match (x->key, key, x->keylen))
		x = x->child[check_bit (key, x->keylen)];

	if (x->keylen == keylen){
		if (netmask) {
			while (x && x->rn_mask != netmask)
				x = x->rn_dupedkey;
		}
		dprint(("ptree_match End\n"));
		return x;
	}

	dprint(("ptree_match End\n"));
	return NULL;
}

/* ptree_search() returns the ptree_node with data
   that matches the key. If data is NULL, it is a branching node,
   and ptree_search() ignores it. no caller reference lock. */
	struct ptree_node *
ptree_search (char *key, int keylen, struct ptree *t)
{
	dprint(("ptree_search Start\n"));
	struct ptree_node *x, *match;

	match = NULL;
	x = t->top;
	while (x && x->keylen <= keylen &&
			ptree_match (x->key, key, x->keylen))
	{
		if (x->data)
			match = x;
		x = x->child[check_bit (key, x->keylen)];
	}

	ptree_node_lock (match);
	dprint(("ptree_search End\n"));
	return match;
}

	static void
ptree_link (struct ptree_node *v, struct ptree_node *w)
{
	dprint(("ptree_link Start\n"));
	/* check the w's key bit just after the v->key (keylen'th bit) */
	int bit;

	bit = check_bit (w->key, v->keylen);
	v->child[bit] = w;
	w->parent = v;
	dprint(("ptree_link End\n"));
}

/* key_common_len() returns the bit length with which the keyi and
   the keyj are equal */
	static int
key_common_len (char *keyi, int keyilen, char *keyj, int keyjlen)
{
	dprint(("ptree_common_len Start\n"));
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
	dprint(("ptree_common_len End\n"));
	return keylen;
}

/* ptree_common() creates and returns the branching node
   between keyi and keyj */
	static struct ptree_node *
ptree_common (char *keyi, int keyilen, char *keyj, int keyjlen)
{
	dprint(("ptree_common Start\n"));
	int keylen;
	struct ptree_node *x;

	keylen = key_common_len (keyi, keyilen, keyj, keyjlen);
	x = ptree_node_create (keyi, keylen);
	if (! x){
		dprint(("ptree_common End\n"));
		return NULL;
	}

	dprint(("ptree_common End\n"));
	return x;
}

/* locks the node */
	void
ptree_node_lock (struct ptree_node *x)
{
	dprint(("ptree_node_lock Start\n"));
	x->lock++;
	dprint(("ptree_node_lock End\n"));
}

/* unlocks the node. if the lock(reference) becomes 0,
   it will be removed. */
	void
ptree_node_unlock (struct ptree_node *x)
{
	dprint(("ptree_node_unlock Start\n"));
	x->lock--;
	if (x->lock == 0)
		ptree_remove (x);
	dprint(("ptree_node_unlock End\n"));
}

/* locks for the tree holding
   but does not lock for the caller reference. */
	static struct ptree_node *
ptree_get (char *key, int keylen, struct ptree *t)
{
	dprint(("ptree_get Start\n"));
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
			/* locks the branching node x for the tree holding */
			ptree_node_lock (x);

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
	/* locks for the tree holding */
	ptree_node_lock (v);
	dprint(("ptree_get End\n"));
	return v;
}

	struct ptree_node *
ptree_add (char *key, int keylen, void *data, struct ptree *t)
{
	dprint(("ptree_add Start\n"));
	struct ptree_node *x;

	x = ptree_get (key, keylen, t);
	if (! x)
	{
		XRTLOG (LOG_ERR, "ptree_add(%p,%d): "
				"ptree_get() failed.\n", key, keylen);
		return NULL;
	}

	x->data = data;
	dprint(("ptree_add End\n"));
	return x;
}

	void
ptree_remove (struct ptree_node *v)
{
	dprint(("ptree_remove Start\n"));
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
	dprint(("ptree_remove End\n"));
}

	struct ptree_node *
ptree_head (struct ptree *t)
{
	dprint(("ptree_head Start\n"));
	if (! t->top){
		dprint(("ptree_head End\n"));
		return NULL;
	}

	ptree_node_lock (t->top);
	dprint(("ptree_head End\n"));
	return t->top;
}

	struct ptree_node *
ptree_next (struct ptree_node *v)
{
	dprint(("ptree_next Start\n"));
	struct ptree_node *t;
	struct ptree_node *u;
	struct ptree_node *w;

	/* if the left child exists, go left */
	if (v->child[0])
	{
		w = v->child[0];
		ptree_node_lock (w);
		ptree_node_unlock (v);
		dprint(("ptree_next End\n"));
		return w;
	}

	if (v->child[1])
	{
		w = v->child[1];
		ptree_node_lock (w);
		ptree_node_unlock (v);
		dprint(("ptree_next End\n"));
		return w;
	}

	u = v->parent;

	if (u->child[0] == v)
	{
		w = u->child[1];
		ptree_node_lock (w);
		ptree_node_unlock (v);
		dprint(("ptree_next End\n"));
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
		
		ptree_node_lock (w);
		ptree_node_unlock (v);
		dprint(("ptree_next End\n"));
		return w;
	}

	/* end of traverse */
	ptree_node_unlock (v);
	dprint(("ptree_next End\n"));
	return NULL;
}

	struct ptree *
ptree_create ()
{
	dprint(("ptree_create Start\n"));
	struct ptree *t;
	struct ptree_node *x;

	XRTMALLOC(t, struct ptree *, sizeof (struct ptree));
	if (! t){
		dprint(("ptree_create End\n"));
		return NULL;
	}
	x = ptree_node_create(0,0);
	x->rn_flags = RNF_ROOT;

	t->top = x;
	dprint(("ptree_create End\n"));
	return t;
}

	void
ptree_delete (struct ptree *t)
{
	dprint(("ptree_delete Start\n"));
	struct ptree_node *x;

	for (x = ptree_head (t); x; x = ptree_next (x))
		ptree_node_delete (x);

	XRTFREE (t);
	dprint(("ptree_delete End\n"));
}
#undef dprint
