#include "opt_inet.h"
#include "opt_inet6.h"
#include "opt_ptree.h"

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/socket.h>
#include <sys/domain.h>
#include <sys/syslog.h>
#include <net/ptree.h>
#include <net/ptree_mpath.h>
#include <net/route.h>
#include <net/if.h>
#include <net/if_var.h>

static char *pn_zeros, *pn_ones;
static int  max_keylen;

#define DEBUG 1
#define dprint(x) { if(DEBUG) printf x; }

	int
debug_node_print(struct ptree_node *pn, int offset)
{
	struct rtentry *rt = pn->data;
	unsigned char *gateway = (unsigned char *)rt->rt_gateway;

	if(pn->key){
	printf("[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d/%d] ",
					(unsigned char)pn->key[0],(unsigned char)pn->key[1],
					(unsigned char)pn->key[2],(unsigned char)pn->key[3],
					(unsigned char)pn->key[4],(unsigned char)pn->key[5],
					(unsigned char)pn->key[6],(unsigned char)pn->key[7],
					(unsigned char)pn->key[8],(unsigned char)pn->key[9],
					(unsigned char)pn->key[10],(unsigned char)pn->key[11],
					pn->keylen - 8*offset);
	}
	if(gateway){
	printf("[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d] ",
					(unsigned char)gateway[0],(unsigned char)gateway[1],
					(unsigned char)gateway[2],(unsigned char)gateway[3],
					(unsigned char)gateway[4],(unsigned char)gateway[5],
					(unsigned char)gateway[6],(unsigned char)gateway[7],
					(unsigned char)gateway[8],(unsigned char)gateway[9],
					(unsigned char)gateway[10],(unsigned char)gateway[11]);
	}
	printf("[0x%x]\n",rt->rt_flags);
	//printf("parent[%p] child[%p, %p]\n",pn->parent,pn->child[0],pn->child[1]);
#endif
	return 0;
}

	int
debug_tree_print(struct ptree_node_head *pnh)
{
		register struct ptree_node *pn, *next;
		if ( !pnh || !pnh->pnh_treetop )
			    goto done;
		pn = pnh->pnh_top;
		printf("pnh[%p] phn_top[%p] offseet[%d]\n",pnh,pn,pnh->pnh_offset);
		printf("dst				gateway			flags\n");
		if(!pn)
			return (0);
		for (;;) {
			if(pn->data)
				debug_node_print(pn, pnh->pnh_offset);
			next = ptree_next(pn);
			if( !next )
				break;
			pn = next;
		}
		/* NOTREACHED */
		return (0);
}

#define LEN(x) (*(const u_char *)(x))


static struct ptree_node *ptree_insert(void *v_arg, void *m_arg,
			   	struct ptree_node_head *head, int *dupentry);
static int ptree_walktree(struct ptree_node_head *h, walktree_f_t *f, void *w);


	static struct ptree_node 
*ptree_insert(v_arg, m_arg, head, dupentry)  
	void *v_arg, *m_arg;
	struct ptree_node_head *head;
	int *dupentry;
{
	caddr_t v = v_arg, m = m_arg;
	register caddr_t cp;
	struct ptree_node *top = head->pnh_top, *t, *tt;
	int len;
	
	len = (int)8*LEN(v);
	if(m && (LEN(m) > head->pnh_offset)){
		unsigned char bitmask = 0xff;
		len = head->pnh_offset;
		while(m[len] & bitmask)
			len++;
		len = 8*len;
	}

	
	if (!top)
		goto on1;
	
	dprint(("-ptree_insert: v[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d/%d]\n",
							(unsigned char)v[0],(unsigned char)v[1],
							(unsigned char)v[2],(unsigned char)v[3],
							(unsigned char)v[4],(unsigned char)v[5],
							(unsigned char)v[6],(unsigned char)v[7],
							(unsigned char)v[8],(unsigned char)v[9],
							(unsigned char)v[10],(unsigned char)v[11],
							len-8*head->pnh_offset));
	if (m_arg)
		dprint(("-ptree_insert: m[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d/%d]\n",
							(unsigned char)m[0],(unsigned char)m[1],
							(unsigned char)m[2],(unsigned char)m[3],
							(unsigned char)m[4],(unsigned char)m[5],
							(unsigned char)m[6],(unsigned char)m[7],
							(unsigned char)m[8],(unsigned char)m[9],
							(unsigned char)m[10],(unsigned char)m[11],
							len-8*head->pnh_offset));
	t = ptree_search(v, len, head->pnh_treetop);
	if (!t)
		goto on1;
	cp = v;
	len = t->keylen;
	{
		register caddr_t cp2 = t->key;
		caddr_t cplim = v;
		if ( !memcmp(cp2,cplim,t->keylen) ){
			*dupentry = 1;  
			return t;
		}
	}
on1:
	*dupentry = 0;
	{
		int *data = NULL;
		tt = ptree_add(v, len, data, head->pnh_treetop);
		if(m && (LEN(m) > head->pnh_offset))
			tt->mask = m;
		else
			tt->mask = NULL;
	}
	dprint(("-ptree_insert End: insert tt = %p\n",tt));
	return (tt);
}


	int
ptree_refines(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	register caddr_t m = m_arg, n = n_arg;
	register caddr_t lim, lim2 = lim = n + LEN(n);
	int longer = LEN(n++) - (int)LEN(m++);
	int masks_are_equal = 1;

	if (longer > 0)
		lim -= longer;
	while (n < lim) {
		if (*n & ~(*m))
			return 0;
		if (*n++ != *m++)
			masks_are_equal = 0;
	}
	while (n < lim2)
		if (*n++)
			return 0;
	if (masks_are_equal && (longer < 0))
		for (lim2 = m - longer; m < lim2; )
			if (*m++)
				return 1;
	return (!masks_are_equal);
}


	struct ptree_node *
ptree_matchaddr(v_arg, head)
	void *v_arg;
	struct ptree_node_head *head;
{
	dprint(("-ptree_matchaddr Start: pnh[%p]\n",head));
	caddr_t v = v_arg;
	register struct ptree_node *t = head->pnh_top;
	if(!t){
		dprint(("-ptree_matchaddr: top = NULL\n"));
		goto miss;
	}
	
	register caddr_t cp;
	caddr_t cplim;
	struct ptree_node *saved_t;
	int vlen;
	
	vlen = (int)8*LEN(v);
	dprint(("-ptree_matchaddr: v[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d/%d]\n",
							(unsigned char)v[0],(unsigned char)v[1],
							(unsigned char)v[2],(unsigned char)v[3],
							(unsigned char)v[4],(unsigned char)v[5],
							(unsigned char)v[6],(unsigned char)v[7],
							(unsigned char)v[8],(unsigned char)v[9],
							(unsigned char)v[10],(unsigned char)v[11],
							vlen-8*head->pnh_offset));
	t = saved_t = ptree_search(v, vlen, head->pnh_treetop);
	if( !saved_t )
		return 0;

	cp = t->key; cplim = v; vlen = t->keylen;
	dprint(("-ptree_matchaddr: cp[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d/%d]\n",
							(unsigned char)cp[0],(unsigned char)cp[1],
							(unsigned char)cp[2],(unsigned char)cp[3],
							(unsigned char)cp[4],(unsigned char)cp[5],
							(unsigned char)cp[6],(unsigned char)cp[7],
							(unsigned char)cp[8],(unsigned char)cp[9],
							(unsigned char)cp[10],(unsigned char)cp[11],
							vlen-8*head->pnh_offset));
	if ( !memcmp(cp,cplim,vlen) )
			goto miss;
	dprint(("-ptree_matchaddr: match exactly as a host\n"));
	/*
	 * match exactly as a host.
	 */
	dprint(("-ptree_matchaddr: return t = %p\n",t));
	return t;
}


		struct ptree_node *
ptree_addroute(v_arg, n_arg, head, rt_node)
		void *v_arg, *n_arg;
		struct ptree_node_head *head;
		struct ptree_node *rt_node;
{
		register struct ptree_node *tt;
		struct ptree_node *saved_tt;
		int keyduplicated;
		/*
		 * Deal with duplicated keys: attach node to previous instance
		 */
		saved_tt = tt = ptree_insert(v_arg, n_arg, head, &keyduplicated);
#if 0 /* multi path */
		if (keyduplicated) {
				for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
						if (tt->rn_mask == netmask){
								dprint(("-ptree_addroute End(keyduplicated)\n"));
								return (0);
						}
						if (netmask == 0 ||
										(tt->rn_mask &&
										 ((b_leaf < tt->rn_bit) /* index>node */
										  || ptree_refines(netmask, tt->rn_mask)
										  || ptree_lexobetter(netmask, tt->rn_mask))))
								break;
				}

				if (tt == saved_tt) {
						struct	ptree_node *xx = x;
						/* link in at head of list */
						(tt = treenodes)->rn_dupedkey = t;
						tt->rn_flags = t->rn_flags;
						tt->rn_parent = x = t->rn_parent;
						t->rn_parent = tt;	 		/* parent */
						//if (x->rn_left == t)
						//		x->rn_left = tt;
						//else
						//		x->rn_right = tt;
						saved_tt = tt; x = xx;
				} else {
						(tt = treenodes)->rn_dupedkey = t->rn_dupedkey;
						t->rn_dupedkey = tt;
						tt->rn_parent = t;			/* parent */
						if (tt->rn_dupedkey)			/* parent */
								tt->rn_dupedkey->rn_parent = tt; /* parent */
				}

				tt->key = (caddr_t) v;
				tt->rn_bit = -1;
				tt->rn_flags = RNF_ACTIVE;
		}
#endif /* mluti path */
		return tt;
}


		struct ptree_node *
ptree_deladdr(v_arg, netmask_arg, head)
		void *v_arg, *netmask_arg;
		struct ptree_node_head *head;
{
		dprint(("-ptree_deladdr Start: pnh[%p]\n",head));
		register struct ptree_node *tt;
		struct ptree_node *saved_tt, *top;
		caddr_t v, netmask;
		unsigned int len;

		v = v_arg;
		netmask = netmask_arg;
		top = head->pnh_top;
		len = (int)8*LEN(v);

		if(netmask && (LEN(netmask) > head->pnh_offset)){
			unsigned char bitmask = 0xff;
			len = head->pnh_offset;
			while(netmask[len] == bitmask)
				len++;
			len = 8*len;
		}

		dprint(("-ptree_deladdr: v[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d/%d]\n",
								(unsigned char)v[0],(unsigned char)v[1],
								(unsigned char)v[2],(unsigned char)v[3],
								(unsigned char)v[4],(unsigned char)v[5],
								(unsigned char)v[6],(unsigned char)v[7],
								(unsigned char)v[8],(unsigned char)v[9],
								(unsigned char)v[10],(unsigned char)v[11],
								len-8*head->pnh_offset));
		saved_tt = tt = ptree_search(v, len, head->pnh_treetop);

		if (!tt){
				dprint(("-ptree_deladdr End: ptree_node nothing\n"));
				return (0);
		}
		register caddr_t cp, cplim;
		cp = tt->key; cplim = v;
		unsigned char *d = (unsigned char *)cp;
		dprint(("-ptree_deladdr: searched-key[%d.%d.%d.%d|%d.%d.%d.%d|%d.%d.%d.%d]\n",
								(unsigned char)d[0],(unsigned char)d[1],
								(unsigned char)d[2],(unsigned char)d[3],
								(unsigned char)d[4],(unsigned char)d[5],
								(unsigned char)d[6],(unsigned char)d[7],
								(unsigned char)d[8],(unsigned char)d[9],
								(unsigned char)d[10],(unsigned char)d[11]));
		if ( memcmp(cp, cplim, len) != 0 ){
				dprint(("-ptree_deladdr End: not match\n"));
				return (0);
		}
		ptree_remove(tt);
		dprint(("-ptree_deladdr End: tt = %p\n",saved_tt));
		return (tt);
}


		static int
ptree_walktree(h, f, w)
		struct ptree_node_head *h;
		walktree_f_t *f;
		void *w;
{
		struct ptree_node *base, *next;
		register struct ptree_node *rn = h->pnh_top;
		if (!rn)
				return (0);

		for (;;) {
				base = rn;
				next = ptree_next(base);
				if( !next )
						return (0);
				rn = next;
		}
		/* NOTREACHED */
}

		int
ptree_inithead(void **head, int off)
{
		register struct ptree_node_head *pnh;
		register struct ptree *top;
		register struct ptree_node *t;

		if (*head)
				return (1);
		
		R_Zalloc(pnh, struct ptree_node_head *, sizeof (*pnh));
		R_Zalloc(top, struct ptree *, sizeof (*top));
		if ( !pnh || !top )
				return (0);

#ifdef _KERNEL
		RADIX_NODE_HEAD_LOCK_INIT(pnh);
#endif
		*head = pnh;
		top->top = t = NULL;
#ifdef PTREE_MPATH
		pnh->pnh_multipath = 1;
#endif
		pnh->pnh_offset = off / 8;
		pnh->rnh_addaddr = ptree_addroute;
		pnh->rnh_deladdr = ptree_deladdr;
		pnh->rnh_matchaddr = ptree_matchaddr;
		pnh->rnh_lookup = ptree_lookup;
		pnh->rnh_walktree = ptree_walktree;
		pnh->pnh_treetop = top;
		return (1);
}

		void
ptree_init()
{
		char *cp, *cplim;
#ifdef _KERNEL
		struct domain *dom;

		for (dom = domains; dom; dom = dom->dom_next) 
				if (dom->dom_maxrtkey > max_keylen)
						max_keylen = dom->dom_maxrtkey;
#endif
		if (max_keylen == 0) {
				log(LOG_ERR,
								"rn_init: ptree functions require max_keylen be set\n");
				return;
		}
		R_Malloc(pn_zeros, char *, 3 * max_keylen);
		if (pn_zeros == NULL) 
				panic("ptree_init");
		bzero(pn_zeros, 3 * max_keylen);
		pn_ones = cp = pn_zeros + max_keylen;
		cplim = pn_ones + max_keylen;
		while (cp < cplim)
				*cp++ = -1;

}

/*
 *  functions for multi path routing.
 */
#ifdef PTREE_MPATH
		int
ptree_mpath_capable(struct ptree *rnh)
{
		return rnh->rnh_multipath;
}

		uint32_t
ptree_mpath_count(struct ptree_node *rn)
{
		dprint(("ptree_mpath_count Start\n"));
		struct ptree_node **rn1;
		uint32_t i = 0;
		rn1 = rn->mpath_array;
		/* count mpath_array */
		while (rn1 != NULL) {
				rn1++;
				i++;
		}
		dprint(("ptree_mpath_count End: count = %d\n",i));
		return (i);
}

		struct rtentry *
rt_mpath_matchgate(struct rtentry *rt, struct sockaddr *gate)
{
		uint32_t	i = 0;
		struct ptree_node *rn, **match;

		rn = (struct ptree_node *)rt;
		if (!rn->mpath_array)
				return rt;
		else
				match = rn->mpath_array;

		if (!gate)
				return NULL;

		/* beyond here, we use rn as the master copy */
		do {
				rt = (struct rtentry *)match;
				/*
				 * we are removing an address alias that has 
				 * the same prefix as another address
				 * we need to compare the interface address because
				 * rt_gateway is a special sockadd_dl structure
				 */
				if (rt->rt_gateway->sa_family == AF_LINK) {
						if (!memcmp(rt->rt_ifa->ifa_addr, gate, gate->sa_len))
								break;
				} else {
						if (rt->rt_gateway->sa_len == gate->sa_len &&
										!memcmp(rt->rt_gateway, gate, gate->sa_len))
								break;
				}
				i++;
		} while ( (match++) != NULL);

		return (struct rtentry *)rn;
}

/* 
 * go through the chain and unlink "rt" from the list
 * the caller will free "rt"
 */
static uint32_t hashjitter;

		int
rt_mpath_delete(struct rtentry *headrt, struct rtentry *rt)
{
		dprint(("rt_mpath_delete Start\n"));
		uint32_t i = 0, n;
		struct ptree_node *t, **t1;

		t = (struct ptree_node *)headrt;
		if (!headrt || !rt)
				return (0);

		n = ptree_mpath_count(t);
		t1 = t->mpath_array;
		while (t1) {
				if ((struct rtentry *)t1 == rt) {
						t->mpath_array[i] = t->mpath_array[n-1];
						t->mpath_array[n-1] = NULL;
						return (1);
				}
				t1++;
		}
		dprint(("rt_mpath_delete End\n"));
		return (0);
}

/*
 * check if we have the same key/mask/gateway on the table already.
 */
		int
rt_mpath_conflict(struct ptree *rnh, struct rtentry *rt,
				struct sockaddr *netmask)
{
		struct ptree_node *rn, **rn1;
		struct rtentry *rt1;
		char *p, *q, *eq;
		int same, l, skip;

		rn = rnh->rnh_lookup(rt_key(rt), netmask, (int)LEN(rt_key(rt)), rnh);
		if (!rn)
				return 0;

		/*
		 * unlike other functions we have in this file, we have to check
		 * all key/mask/gateway as rnh_lookup can match less specific entry.
		 */
		rt1 = (struct rtentry *)rn;

		/* compare key. */
		if (rt_key(rt1)->sa_len != rt_key(rt)->sa_len ||
						bcmp(rt_key(rt1), rt_key(rt), rt_key(rt1)->sa_len))
				goto different;

		/* key was the same.  compare netmask.  hairy... */
		if (rt_mask(rt1) && netmask) {
				skip = rnh->rnh_treetop->rn_offset;
				if (rt_mask(rt1)->sa_len > netmask->sa_len) {
						/*
						 * as rt_mask(rt1) is made optimal by radix.c,
						 * there must be some 1-bits on rt_mask(rt1)
						 * after netmask->sa_len.  therefore, in
						 * this case, the entries are different.
						 */
						if (rt_mask(rt1)->sa_len > skip)
								goto different;
						else {
								/* no bits to compare, i.e. same*/
								goto maskmatched;
						}
				}

				l = rt_mask(rt1)->sa_len;
				if (skip > l) {
						/* no bits to compare, i.e. same */
						goto maskmatched;
				}
				p = (char *)rt_mask(rt1);
				q = (char *)netmask;
				if (bcmp(p + skip, q + skip, l - skip))
						goto different;
				/*
				 * need to go through all the bit, as netmask is not
				 * optimal and can contain trailing 0s
				 */
				eq = (char *)netmask + netmask->sa_len;
				q += l;
				same = 1;
				while (eq > q)
						if (*q++) {
								same = 0;
								break;
						}
				if (!same)
						goto different;
		} else if (!rt_mask(rt1) && !netmask)
				; /* no mask to compare, i.e. same */
		else {
				/* one has mask and the other does not, different */
				goto different;
		}

maskmatched:
		rn1 = rn->mpath_array;
		/* key/mask were the same.  compare gateway for all multipaths */
		do {
				rt1 = (struct rtentry *)rn1;
				if (rt1->rt_gateway->sa_family == AF_LINK) {
						if (rt1->rt_ifa->ifa_addr->sa_len != rt->rt_ifa->ifa_addr->sa_len ||
										bcmp(rt1->rt_ifa->ifa_addr, rt->rt_ifa->ifa_addr, 
												rt1->rt_ifa->ifa_addr->sa_len))
								continue;
				} else {
						if (rt1->rt_gateway->sa_len != rt->rt_gateway->sa_len ||
										bcmp(rt1->rt_gateway, rt->rt_gateway,
												rt1->rt_gateway->sa_len))
								continue;
				}

				/* all key/mask/gateway are the same.  conflicting entry. */
				return EEXIST;
		} while ((rn1++) != NULL);

different:
		return 0;
}

		void
rtalloc_mpath_fib(struct route *ro, uint32_t hash, u_int fibnum)
{
		u_int32_t n;
		struct rtentry *rt, *rt0;
		struct ptree_node *rn;

		/*
		 * XXX we don't attempt to lookup cached route again; what should
		 * be done for sendto(3) case?
		 */
		if (ro->ro_rt && ro->ro_rt->rt_ifp && (ro->ro_rt->rt_flags & RTF_UP))
				return;				 
		ro->ro_rt = rtalloc1_fib(&ro->ro_dst, 1, 0, fibnum);
		rn = (struct ptree_node *)ro->ro_rt;
		/* if the route does not exist or it is not multipath, don't care */
		if (ro->ro_rt == NULL)
				return;
		if (rn->mpath_array == NULL) {
				RT_UNLOCK(ro->ro_rt);
				return;
		}

		/* beyond here, we use rn as the master copy */
		rt0 = ro->ro_rt;
		n = ptree_mpath_count(rn);

		/* gw selection by Modulo-N Hash (RFC2991) XXX need improvement? */
		hash += hashjitter;
		hash %= n;
		rn = rn->mpath_array[n];
		rt = (struct rtentry *)rn;
		/* XXX try filling rt_gwroute and avoid unreachable gw  */

		/* gw selection has failed - there must be only zero weight routes */
		if (!rt) {
				RT_UNLOCK(ro->ro_rt);
				ro->ro_rt = NULL;
				return;
		}
		if (ro->ro_rt != rt) {
				RTFREE_LOCKED(ro->ro_rt);
				ro->ro_rt = rt;
				RT_LOCK(ro->ro_rt);
				RT_ADDREF(ro->ro_rt);

		} 
		RT_UNLOCK(ro->ro_rt);
}

extern int	in6_inithead(void **head, int off);
extern int	in_inithead(void **head, int off);

#ifdef INET
		int
ptree4_mpath_inithead(void **head, int off)
{
		struct ptree *rnh;

		hashjitter = arc4random();
		if (in_inithead(head, off) == 1) {
				rnh = (struct ptree *)*head;
				rnh->rnh_multipath = 1;
				return 1;
		} else
				return 0;
}
#endif

#ifdef INET6
		int
ptree6_mpath_inithead(void **head, int off)
{
		struct ptree *rnh;

		hashjitter = arc4random();
		if (in6_inithead(head, off) == 1) {
				rnh = (struct ptree *)*head;
				rnh->rnh_multipath = 1;
				return 1;
		} else
				return 0;
}
#endif
#endif /* PTREE_MPATH */

#undef dprint
#undef DEBUG
