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
static int      max_keylen;

#define DEBUG 1
#define dprint(x) { if(DEBUG) printf x; }

#ifdef DEBUG
#include <sys/types.h>
#include <netinet/in.h>
		
	int
debug_node_print(struct ptree_node *pn)
{
	printf("node[%p] ",pn);
	if( pn->key ){
		printf("key[%d.%d.%d.%d.%d.%d.%d.%d/%d] ",
						(unsigned char)pn->key[0],
						(unsigned char)pn->key[1],
						(unsigned char)pn->key[2],
						(unsigned char)pn->key[3],
						(unsigned char)pn->key[4],
						(unsigned char)pn->key[5],
						(unsigned char)pn->key[6],
						(unsigned char)pn->key[7],
						pn->keylen);
	}
	//if( rn->rn_mask ){
	//	ip = (unsigned char *)rn->rn_mask;
	//	printf("mask %d.%d.%d.%d: ",ip[0],ip[1],ip[2],ip[3]);
	//}
	//printf("rn_bit %d ",rn->rn_bit);
	//if( rn->rn_bmask ) printf("rn_bmask 0x%x\n",rn->rn_bmask);
	printf("data[%p] ",pn->data);
	printf("parent[%p] ",pn->parent);
	printf("[%p, %p]\n",pn->child[0],pn->child[1]);
	//printf("rn_dupedkey = %p\n",rn->rn_dupedkey);
	//printf("rn_offset %d\n",rn->rn_Off);
#if 0
	rm = rn->rn_mklist;
	while(rm){
		printf("/*+++++++++++++++++++++++++*/\n");
		printf("- mklist = %p\n",rm);
		printf("- rm_bit %d rm_flags 0x%x\n",rm->rm_bit,rm->rm_flags);
		printf("- rm_unused 0x%x\n",rm->rm_unused);
		if(rm->rm_mask){
			ip = (unsigned char *)rm->rm_mask;
			printf("- rm_mask %d.%d.%d.%d\n",ip[3],ip[2],ip[1],ip[0]);
		}
		printf("- rm_leaf = %p\n",rm->rm_leaf);
		printf("- rm_refs = %d\n",rm->rm_refs);
		printf("/*+++++++++++++++++++++++++*/\n");
		rm = rm->rm_mklist;
	}
#endif
	return 0;
}

	int
debug_tree_print(struct ptree_node_head *pnh)
{
		printf("======= Debug tree print Start =======\n");
		register struct ptree_node *pn, *next;
		if ( !pnh || !pnh->pnh_treetop )
			    goto done;
		pn = pnh->pnh_top;
		printf("ptree = %p treetop = %p\n",pnh,pn);
		if(!pn)
			goto done;
		for (;;) {
			debug_node_print(pn);
			next = ptree_next(pn);
			if( !next )
				break;
			pn = next;
		}
		/* NOTREACHED */
done:
		printf("======= Debug tree print End =======\n");
		return (0);
}
#endif /* DEBUG */

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
	dprint(("-ptree_insert Start\n"));
	caddr_t v = v_arg, m = m_arg;
	register caddr_t cp;
	struct ptree_node *top = head->pnh_top, *t, *tt;
	int len;
	if (m)
			len = (int)LEN(m);
	else
			len = (int)LEN(v);
	dprint(("-ptree_insert: len = %d\n",len));
	
	if (!top){
		dprint(("-ptree_insert: top = NULL\n"));
		goto on1;
	}
	//int head_off = top->rn_offset;
	t = ptree_search(v, len, head->pnh_treetop);
	cp = v;// + head_off;
	dprint(("-ptree_insert: t = %p mask_len = %d\n",t,len));
	
	/* Find first bit at which v and t->rn_key differ */ 
	{
		register caddr_t cp2 = t->key;// + head_off;
		//register int cmp_res;
		caddr_t cplim = v + len;
		
		dprint(("-ptree_insert: "));
		while (cp < cplim){
			dprint((" + "));
			if (*cp2++ != *cp++){
				dprint(("goto on1\n"));
				goto on1;
			}
		}
		dprint(("key dupentry\n"));
		*dupentry = 1;  
		return t;
#if 0
on1:
		dprint(("-ptree_insert: on1\n"));
		cmp_res = (cp[-1] ^ cp2[-1]) & 0xff;
		for (b = (cp - v) << 3; cmp_res; b--)
			cmp_res >>= 1;
		dprint(("-ptree_insert: first different bit = %d\n",b));
#endif
on1:
		*dupentry = 0;
	}
	{
		//register struct ptree_node *p, *x = top;
		int *data;
		data = &len;
		dprint(("-ptree_insert: data = %d\n",*data));
#if 0
		cp = v;
		do {
			p = x;
			if (cp[x->rn_offset] & x->rn_bmask)
				x = x->rn_right;
			else
				x = x->rn_left;
			dprint(("-ptree_insert: x = %p\n",x));
			if (!x) break;
		}
		while (b > (unsigned) x->rn_bit);
		/* x->rn_bit < b && x->rn_bit >= 0 */
#endif
#ifdef RN_DEBUG
		if (rn_debug)
			log(LOG_DEBUG, "rn_insert: Going In:\n"), traverse(p);
#endif 
		tt = ptree_add(v, len, data, head->pnh_treetop);
		tt->mask = m;
#ifdef RN_DEBUG
		if (rn_debug)
			log(LOG_DEBUG, "rn_insert: Coming Out:\n"), traverse(p);
#endif
	}
	dprint(("-ptree_insert End: insert tt = %p\n",tt));
	return (tt);
}


	int
ptree_refines(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	dprint(("-ptree_refines Start\n"));
	dprint(("-ptree_refines: m_arg = %p, n_arg = %p\n",m_arg,n_arg));

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
		if (*n++){
			dprint(("-ptree_refines End 1\n"));
			return 0;
		}
	if (masks_are_equal && (longer < 0))
		for (lim2 = m - longer; m < lim2; )
			if (*m++){
				dprint(("-ptree_refines End 2\n"));
				return 1;
			}
	dprint(("-ptree_refines End 3\n"));
	return (!masks_are_equal);
}


	struct ptree_node *
ptree_matchaddr(v_arg, head)
	void *v_arg;
	struct ptree_node_head *head;
{
	dprint(("-ptree_matchaddr Start\n"));
	caddr_t v = v_arg;
	register struct ptree_node *t = head->pnh_top;
	if(!t){
		dprint(("-ptree_matchaddr: top = NULL\n"));
		goto miss;
	}
	
	register caddr_t cp = v, cp2;
	caddr_t cplim;
	struct ptree_node *saved_t;
	int /*off = t->rn_offset, */vlen = LEN(cp);//, matched_off;
	//register int test, b, rn_bit;

	dprint(("-ptree_matchaddr: v = %p vlen = %d head = %p top = %p\n",
							v,vlen,head,t));
	t = saved_t = ptree_search(v, vlen, head->pnh_treetop);
	if( !saved_t ){
		dprint(("-ptree_matchaddr: search result is NULL\n"));
		goto miss;
	}
#if 0
	if (t->rn_mask){
		vlen = *(u_char *)t->rn_mask;
		dprint(("-ptree_matchaddr: if(t->rn_mask) vlen = %d\n",vlen));
	}
#endif
	/*cp += off; */cp2 = t->key;/* + off*/ cplim = v + vlen;
	dprint(("-ptree_matchaddr:"));
	for (; cp < cplim; cp++, cp2++){
		dprint((" + "));	
		if (*cp != *cp2){
			dprint(("goto on1\n"));
			goto on1;
		}
	}
	dprint(("-ptree_matchaddr: match exactly as a host\n"));
	/*
	 * match exactly as a host.
	 */
	dprint(("-ptree_matchaddr: return t = %p\n",t));
	debug_node_print(t);
	return t;
on1:
#if 0
	/*
	 * Even if we don't match exactly as a host,
	 * we may match if the leaf we wound up at is
	 * a route to a net.
	 */
	dprint(("-ptree_matchaddr: on1\n"));
	test = (*cp ^ *cp2) & 0xff; /* find first bit that differs */
	dprint(("-ptree_matchaddr: first bit that diff = 0x%x\n",test));
	for (b = 7; (test >>= 1) > 0;){
		b--;
	}
	
	matched_off = cp - v;
	dprint(("-ptree_matchaddr: matched_off = 0x%x\n",matched_off));
	b += matched_off << 3;
	rn_bit = -1 - b;
	dprint(("-ptree_matchaddr: rn_bit = %d t->rn_bit = %d\n",
							rn_bit,t->rn_bit));
	
	if (t->rn_flags & RNF_NORMAL) {
			if (rn_bit <= t->rn_bit){
					dprint(("-ptree_matchaddr End 2\n"));
					return t;
			}
	} else if (ptree_satisfies_leaf(v, t, matched_off)){
			dprint(("-ptree_matchaddr End 3\n"));
			return t;
	}
		
	t = saved_t;
	register struct ptree_mask *m;
	m = t->rn_mklist;
	while (m) {
			if (m->rm_flags & RNF_NORMAL) {
					dprint(("-ptree_matchaddr: rn_bit = %d rm_bit = %d\n",rn_bit,m->rm_bit));
					if (rn_bit <= m->rm_bit){
						dprint(("-ptree_matchaddr: m->rm_leaf = %p\n",m->rm_leaf));
						debug_node_print(m->rm_leaf);
						return (m->rm_leaf);
					}
			}
			else {
					off = min(t->rn_offset, matched_off);
					dprint(("-ptree_matchaddr: off = %d\n",off));
					//x = ptree_search_m(v, t, m->rm_mask);
					while (t && t->rn_mask != m->rm_mask)
							t = t->rn_dupedkey;
					if (t && ptree_satisfies_leaf(v, t, off)){
							dprint(("-ptree_matchaddr End: return %p\n",t));
							return t;
					}
			}
			m = m->rm_mklist;
			dprint(("-ptree_matchaddr: next rm_mklist = %p\n",m));
	}
#endif
miss:
	dprint(("-ptree_matchaddr End: miss\n"));
	return 0;
}


		struct ptree_node *
ptree_addroute(v_arg, n_arg, head, rt_node)
		void *v_arg, *n_arg;
		struct ptree_node_head *head;
		struct ptree_node *rt_node;
{
		dprint(("-ptree_addroute Start head = %p\n",head));
		debug_tree_print(head);

		register struct ptree_node *tt;
		register struct rtentry *rt = (struct rtentry *)&rt_node;
		struct ptree_node *saved_tt;
		int keyduplicated;
		dprint(("-ptree_addroute: key = %p netmask = %p\n",v_arg,n_arg));

#if 0
		if (netmask)  {
				if ((x = ptree_addmask(netmask, 0, top->rn_offset)) == 0){
						dprint(("-ptree_addroute End 1(retrun 0)\n"));
						return (0);
				}
				b_leaf = x->rn_bit;
				b = -1 - x->rn_bit;
				netmask = x->rn_key;
				dprint(("-ptree_addroute: set netmask\n"));
		}
#endif
		/*
		 * Deal with duplicated keys: attach node to previous instance
		 */
		saved_tt = tt = ptree_insert(v_arg, n_arg, head, &keyduplicated);
		dprint(("-ptree_addroute: tt = %p rt = %p keydup = %d\n",
								tt,rt,keyduplicated));
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

#ifdef RN_DEBUG
				t=tt+1; tt->rn_info = rn_nodenum++; t->rn_info = rn_nodenum++;
				tt->rn_twin = t; tt->rn_ybro = rn_clist; rn_clist = tt;
#endif
				tt->key = (caddr_t) v;
				tt->rn_bit = -1;
				tt->rn_flags = RNF_ACTIVE;
		}
#endif /* mluti path */
		dprint(("-ptree_addroute End\n"));
		debug_tree_print(head);
		return tt;
}


		struct ptree_node *
ptree_deladdr(v_arg, netmask_arg, head)
		void *v_arg, *netmask_arg;
		struct ptree_node_head *head;
{
		dprint(("-ptree_deladdr Start\n"));
		debug_tree_print(head);
		register struct ptree_node *tt;
		struct ptree_node *saved_tt, *top;
		caddr_t v, netmask;
		int len;

		v = v_arg;
		netmask = netmask_arg;
		top = head->pnh_top;
		if (netmask)
			len =  LEN(netmask);
		else
			len =  LEN(v);

		saved_tt = tt = ptree_search(v, len, head->pnh_treetop);
		if ((tt == 0) || (memcmp(v, tt->key, len) != 0)){
				dprint(("-ptree_deladdr: not match\n"));
				return (0);
		}
		ptree_remove(tt);
		if (tt == top)
			head->pnh_top = NULL;
		dprint(("-ptree_deladdr End: tt = %p &tt = %p\n",saved_tt,&saved_tt));
		debug_tree_print(head);
		return (tt);
}

#if 0
/*
 * This is the same as rn_walktree() except for the parameters and the
 * exit.
 */
		static int
ptree_walktree_from(h, a, m, f, w)
		struct ptree *h;
		void *a, *m;
		walktree_f_t *f;
		void *w;
{
		dprint(("-ptree_walktree_from Start\n"));
		int error;
		struct ptree_node *base, *next;
		u_char *xa = (u_char *)a;
		u_char *xm = (u_char *)m;
		register struct ptree_node *rn, *last = 0 /* shut up gcc */;
		int stopping = 0;
		int lastb;

		/*
		 * rn_search_m is sort-of-open-coded here. We cannot use the
		 * function because we need to keep track of the last node seen.
		 */
		for (rn = h->rnh_treetop; rn->rn_bit >= 0; ) {
				last = rn;
				if (!(rn->rn_bmask & xm[rn->rn_offset])) {
						break;
				}
				if (rn->rn_bmask & xa[rn->rn_offset]) {
						rn = rn->rn_right;
				} else {
						rn = rn->rn_left;
				}
		}

		/*
		 * Two cases: either we stepped off the end of our mask,
		 * in which case last == rn, or we reached a leaf, in which
		 * case we want to start from the last node we looked at.
		 * Either way, last is the node we want to start from.
		 */
		rn = last;
		lastb = rn->rn_bit;
		/*
		 * This gets complicated because we may delete the node
		 * while applying the function f to it, so we need to calculate
		 * the successor node in advance.
		 */
		while (rn->rn_bit >= 0)
				rn = rn->rn_left;

		while (!stopping) {
				printf("node %p (0x%x)\n", rn, rn->rn_bit);
				base = rn;
				/* If at right child go back up, otherwise, go right */
				while (rn->rn_parent->rn_right == rn
								&& !(rn->rn_flags & RNF_ROOT)) {
						rn = rn->rn_parent;

						/* if went up beyond last, stop */
						if (rn->rn_bit < lastb) {
								stopping = 1;
								printf("up too far\n");
								/*
								 * XXX we should jump to the 'Process leaves'
								 * part, because the values of 'rn' and 'next'
								 * we compute will not be used. Not a big deal
								 * because this loop will terminate, but it is
								 * inefficient and hard to understand!
								 */
						}
				}

				/* Find the next *leaf* since next node might vanish, too */
				for (rn = rn->rn_parent->rn_right; rn->rn_bit >= 0;)
						rn = rn->rn_left;
				next = rn;
				/* Process leaves */
				while ((rn = base) != 0) {
						base = rn->rn_dupedkey;
						printf("leaf %p\n", rn);
						if (!(rn->rn_flags & RNF_ROOT)
										&& (error = (*f)(rn, w)))
								return (error);
				}
				rn = next;

				if (rn->rn_flags & RNF_ROOT) {
						printf("root, stopping");
						stopping = 1;
				}

		}
		dprint(("-ptree_walktree_from End\n"));
		return 0;
}
#endif

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
		dprint(("-ptree_inithead Start\n"));
		register struct ptree_node_head *pnh;
		register struct ptree *top;
		register struct ptree_node *t;

		if (*head){
				dprint(("-ptree_inithead End1\n"));
				return (1);
		}
		R_Zalloc(pnh, struct ptree_node_head *, sizeof (*pnh));
		R_Zalloc(top, struct ptree *, sizeof (*top));
		if ( !pnh || !top ){
				dprint(("-ptree_inithead: R_Zalloc fault\n"));
				return (0);
		}
#ifdef _KERNEL
		RADIX_NODE_HEAD_LOCK_INIT(pnh);
#endif
		*head = pnh;
		top->top = t = NULL;
#ifdef PTREE_MPATH
		pnh->pnh_multipath = 1;
#endif
		pnh->rnh_addaddr = ptree_addroute;
		pnh->rnh_deladdr = ptree_deladdr;
		pnh->rnh_matchaddr = ptree_matchaddr;
		pnh->rnh_lookup = ptree_lookup;
		pnh->rnh_walktree = ptree_walktree;
		//rnh->rnh_walktree_from = ptree_walktree_from;
		pnh->pnh_treetop = top;
		dprint(("-ptree_inithead End (success)\n"));
		return (1);
}

		void
ptree_init()
{
		dprint(("-ptree_init Start\n"));
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
				dprint(("-ptree_init End1\n"));
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
		//if (ptree_inithead((void **)(void *)&mask_rnhead, 0) == 0)
		//		panic("ptree_init 2");

		dprint(("-ptree_init End2\n"));
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
