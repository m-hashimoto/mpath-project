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
#include <net/route.h>
#include <net/if.h>
#include <net/if_var.h>

static char *rn_zeros, *rn_ones, *addmask_key;
static int      max_keylen;
static struct ptree_mask *rn_mkfreelist;
static struct ptree *mask_rnhead;

#define DEBUG 1
#define dprint(x) { if(DEBUG) printf x; }

#define MKGet(m) {                                              \
	if (rn_mkfreelist) {                                    \
		m = rn_mkfreelist;                              \
		rn_mkfreelist = (m)->rm_mklist;                 \
	} else                                                  \
	R_Malloc(m, struct ptree_mask *, sizeof (struct ptree_mask)); }

#define MKFree(m) { (m)->rm_mklist = rn_mkfreelist; rn_mkfreelist = (m);}
#define LEN(x) (*(const u_char *)(x))
#define rn_masktop (mask_rnhead->rnh_treetop)

static struct ptree_node *ptree_search_m(void *v_arg,
	       	struct ptree_node *head, void *m_arg);
static struct ptree_node *ptree_insert(void *v_arg, struct ptree *head,
		int *dupentry, struct ptree_node nodes[2]);
static int ptree_lexobetter(void *m_arg, void *n_arg);
static struct ptree_mask *ptree_new_mask(register struct ptree_node *tt,
	       register struct ptree_mask *next);
		   
static int ptree_walktree_from(struct ptree *h, void *a, void *m, 
		walktree_f_t *f, void *w);
static int ptree_walktree(struct ptree *h, walktree_f_t *f, void *w);
static int ptree_satisfies_leaf(char *trial,
		register struct ptree_node *leaf, int skip);


	static struct ptree_node 
*ptree_insert(v_arg, head, dupentry, nodes)  
	void *v_arg;
	struct ptree *head;   
	int *dupentry; 
	struct ptree_node nodes[2];
{
	dprint(("ptree_insert Start\n"));
	caddr_t v = v_arg;
	dprint(("v = %x:%x:%x:%x head = %p\n",*v,*v+1,*v+2,*v+3,head));
	struct ptree_node *top = head->rnh_treetop;
	int head_off = top->rn_offset, vlen = (int)LEN(v);
	register struct ptree_node *t = ptree_search(v, vlen, head);
	register caddr_t cp = v + head_off; 
	register int b; 
	/* Find first bit at which v and t->rn_key differ */ 
	{         
		register caddr_t cp2 = t->rn_key + head_off;  
		register int cmp_res;
		caddr_t cplim = v + vlen;

		while (cp < cplim) 
			if (*cp2++ != *cp++)
				goto on1;   
		*dupentry = 1;  
		dprint(("ptree_insert End (key dupentry)\n"));
		return t;
on1:
		dprint(("ptree_insert: on1\n"));
		*dupentry = 0;
		cmp_res = (cp[-1] ^ cp2[-1]) & 0xff;  
		for (b = (cp - v) << 3; cmp_res; b--) 
			cmp_res >>= 1;
		dprint(("ptree_insert: first different bit = %d\n",b));
	}
	{
		//register struct ptree_node *p, *x = top;
		int *data;
		data = &vlen;
		dprint(("ptree_insert: data = %d\n",*data));
		cp = v;
#if 0
		do {
			p = x;
			if (cp[x->rn_offset] & x->rn_bmask)
				x = x->rn_right;
			else
				x = x->rn_left;
			dprint(("ptree_insert: x = %p\n",x));
			if (!x) break;
		}
		while (b > (unsigned) x->rn_bit);
		/* x->rn_bit < b && x->rn_bit >= 0 */
#endif
#ifdef RN_DEBUG
		if (rn_debug)
			log(LOG_DEBUG, "rn_insert: Going In:\n"), traverse(p);
#endif 
		t = ptree_add(v, b, data, head);
#ifdef RN_DEBUG
		if (rn_debug)
			log(LOG_DEBUG, "rn_insert: Coming Out:\n"), traverse(p);
#endif
	}
	dprint(("ptree_insert End\n"));
	return (t);
}

	struct ptree_node *
ptree_addmask(n_arg, search, skip)        
	int search, skip;
	void *n_arg;
{
	dprint(("ptree_addmask Start\n"));
	caddr_t netmask = (caddr_t)n_arg;
	register struct ptree_node *x;
	register caddr_t cp, cplim;
	register int b = 0, mlen, j;
	int maskduplicated, m0, isnormal;
	struct ptree_node *saved_x;  
	static int last_zeroed = 0;  
	dprint(("ptree_addmask: search = %d, skip = %d, n_arg = %p\n",search,skip,n_arg));
	if ((mlen = LEN(netmask)) > max_keylen) 
		mlen = max_keylen;
	if (skip == 0)  
		skip = 1; 
	if (mlen <= skip) 
		return (mask_rnhead->rnh_nodes);   
	if (skip > 1) 
		bcopy(rn_ones + 1, addmask_key + 1, skip - 1); 
	if ((m0 = mlen) > skip) 
		bcopy(netmask + skip, addmask_key + skip, mlen - skip);
	/*         * Trim trailing zeroes.         */  
	for (cp = addmask_key + mlen; (cp > addmask_key) && cp[-1] == 0;)
		cp--;
	mlen = cp - addmask_key; 
	if (mlen <= skip) {        
		if (m0 >= last_zeroed)  
			last_zeroed = mlen;  
		dprint(("ptree_addmask End if(mlen<=skip)\n"));
		return (mask_rnhead->rnh_nodes); 
	}     
	if (m0 < last_zeroed)  
		bzero(addmask_key + m0, last_zeroed - m0); 
	*addmask_key = last_zeroed = mlen;
	x = ptree_search(addmask_key, mlen/*(int)LEN(netmask)*/, mask_rnhead);
	if (bcmp(addmask_key, x->rn_key, mlen) != 0)  
		x = 0;  
	if (x || search){
		dprint(("ptree_addmask End if(x||search)\n"));
		return (x);
	}	
	R_Zalloc(x, struct ptree_node *, max_keylen + 2 * sizeof (*x));
	if ((saved_x = x) == 0){
		dprint(("ptree_addmask End if(saved_x==0)\n"));
		return (0);
	}
	netmask = cp = (caddr_t)(x + 2);
	bcopy(addmask_key, cp, mlen);
	x = ptree_insert(cp, mask_rnhead, &maskduplicated, x);
	if (maskduplicated) { 
		log(LOG_ERR, "rn_addmask: mask impossibly already in tree");
		Free(saved_x);
		dprint(("ptree_addmask End if(maskduplicated)\n"));
		return (x);
	}
	cplim = netmask + mlen;
	isnormal = 1;
	for (cp = netmask + skip; (cp < cplim) && *(u_char *)cp == 0xff;)
		cp++;
	if (cp != cplim) {
		static char normal_chars[] = {
			0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff};

		for (j = 0x80; (j & *cp) != 0; j >>= 1)
			b++;
		if (*cp != normal_chars[b] || cp != (cplim - 1))
			isnormal = 0;
	}
	b += (cp - netmask) << 3;
	dprint(("ptree_addmask: x->rn_bit = %d\n",x->rn_bit));
	x->rn_bit = -1 - b;
	if (isnormal)
		x->rn_flags |= RNF_NORMAL;
	
	dprint(("ptree_addmask End\n"));
	return (x);
}


/*
 * Same as above, but with an additional mask.
 * XXX note this function is used only once.
 */
	static struct ptree_node *
ptree_search_m(v_arg, head, m_arg)
	struct ptree_node *head;
	void *v_arg, *m_arg;
{
	dprint(("ptree_seach_m Start\n"));
	dprint(("v_arg = %p, head = %p, m_arg = %p\n",v_arg,head,m_arg));

	register struct ptree_node *x, *y;
	register caddr_t v = v_arg, m = m_arg;

	for (x = head; x->rn_bit >= 0;) {
		y = x;
		if ((y->rn_bmask & m[y->rn_offset]) &&
				(y->rn_bmask & v[y->rn_offset]))
			x = y->rn_right;
		else
			x = y->rn_left;
		if ( !x || (x->rn_bit <= y->rn_bit) )
			break;
	}
	dprint(("ptree_seach_m End\n"));
	return x;
}


	int
ptree_refines(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	dprint(("ptree_refines Start\n"));
	dprint(("m_arg = %p, n_arg = %p\n",m_arg,n_arg));

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
			dprint(("ptree_refines End 1\n"));
			return 0;
		}
	if (masks_are_equal && (longer < 0))
		for (lim2 = m - longer; m < lim2; )
			if (*m++){
				dprint(("ptree_refines End 2\n"));
				return 1;
			}
	dprint(("ptree_refines End 3\n"));
	return (!masks_are_equal);
}

	static int      
ptree_lexobetter(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	dprint(("ptree_lexobetter Start\n"));
	register u_char *mp = m_arg, *np = n_arg, *lim;

	if (LEN(mp) > LEN(np)){	
		dprint(("ptree_lexobetter End 1\n"));
		return 1;
	}
      	/* not really, but need to check longer one first */   
	if (LEN(mp) == LEN(np))
		for (lim = mp + LEN(mp); mp < lim;)
			if (*mp++ > *np++){
				dprint(("ptree_lexobetter End 2\n"));
				return 1;
			}
	dprint(("ptree_lexobetter End 3\n"));
	return 0;
}

	static struct ptree_mask *
ptree_new_mask(tt, next)
	register struct ptree_node *tt; 
	register struct ptree_mask *next;
{
	dprint(("ptree_new_mask Start\n"));
	register struct ptree_mask *m;

	MKGet(m);
	if (m == 0) {
		log(LOG_ERR, "Mask for route not entered\n");
		dprint(("ptree_new_mask End 1\n"));
		return (0);
	}
	bzero(m, sizeof *m);
	m->rm_bit = tt->rn_bit;
	m->rm_flags = tt->rn_flags;
	if (tt->rn_flags & RNF_NORMAL)
		m->rm_leaf = tt;
	else
		m->rm_mask = tt->rn_mask;
	m->rm_mklist = next;
	tt->rn_mklist = m;
	dprint(("ptree_new_mask End 2\n"));
	return m;
}

	static int
ptree_satisfies_leaf(trial, leaf, skip)
	char *trial;
	register struct ptree_node *leaf;
	int skip;
{
	dprint(("ptree_satisfines_leaf Start\n"));
	register char *cp = trial, *cp2 = leaf->rn_key, *cp3 = leaf->rn_mask;
	char *cplim;
	int length = min(LEN(cp), LEN(cp2));

	if (cp3 == 0)
		cp3 = rn_ones;
	else
		length = min(length, *(u_char *)cp3);
	cplim = cp + length; cp3 += skip; cp2 += skip;
	for (cp += skip; cp < cplim; cp++, cp2++, cp3++)
		if ((*cp ^ *cp2) & *cp3){
			dprint(("ptree_satisfines_leaf End 1\n"));
			return 0;
		}
	dprint(("ptree_satisfines_leaf End 2\n"));
	return 1;
}

	struct ptree_node *
ptree_matchaddr(v_arg, head)
	void *v_arg;
	struct ptree *head;
{
	dprint(("ptree_matchaddr Start\n"));
	caddr_t v = v_arg;
	register struct ptree_node *t = head->top, *x;
	register caddr_t cp = v, cp2;
	caddr_t cplim;
	struct ptree_node *saved_t;
	int off = t->rn_offset, vlen = LEN(cp), matched_off;
	register int test, b, rn_bit;

	t = saved_t = ptree_search(v, vlen, head);

	/*
	 * See if we match exactly as a host destination
	 * or at least learn how many bits match, for normal mask finesse.
	 *
	 * It doesn't hurt us to limit how many bytes to check
	 * to the length of the mask, since if it matches we had a genuine
	 * match and the leaf we have is the most specific one anyway;
	 * if it didn't match with a shorter length it would fail
	 * with a long one.  This wins big for class B&C netmasks which
	 * are probably the most common case...
	 */
	if (t->rn_mask)
		vlen = *(u_char *)t->rn_mask;
	cp += off; cp2 = t->rn_key + off; cplim = v + vlen;
	for (; cp < cplim; cp++, cp2++)
		if (*cp != *cp2)
			goto on1;
	/*
	 * This extra grot is in case we are explicitly asked
	 * to look up the default.  Ugh!
	 *
	 * Never return the root node itself, it seems to cause a
	 * lot of confusion.
	 */
	if (t->rn_flags & RNF_ROOT)
		t = t->rn_dupedkey;
	dprint(("ptree_matchaddr End 1\n"));
	return t;
on1:
	test = (*cp ^ *cp2) & 0xff; /* find first bit that differs */
	for (b = 7; (test >>= 1) > 0;)
		b--;
	matched_off = cp - v;
	b += matched_off << 3;
	rn_bit = -1 - b;
	/*
	 * If there is a host route in a duped-key chain, it will be first.
	 */
	if ((saved_t = t)->rn_mask == 0)
		t = t->rn_dupedkey;
	for (; t; t = t->rn_dupedkey)
		/*
		 * Even if we don't match exactly as a host,
		 * we may match if the leaf we wound up at is
		 * a route to a net.
		 */
		if (t->rn_flags & RNF_NORMAL) {
			if (rn_bit <= t->rn_bit){
				dprint(("ptree_matchaddr End 2\n"));
				return t;
			}
		} else if (ptree_satisfies_leaf(v, t, matched_off)){
			dprint(("ptree_matchaddr End 3\n"));
			return t;
		}	
	t = saved_t;
	
	register struct ptree_mask *m;
	m = t->rn_mklist;
	/*
	 * If non-contiguous masks ever become important
	 * we can restore the masking and open coding of
	 * the search and satisfaction test and put the
	 * calculation of "off" back before the "do".
	 */
	while (m) {
		if (m->rm_flags & RNF_NORMAL) {
			if (rn_bit <= m->rm_bit)
				return (m->rm_leaf);
		} else {
			off = min(t->rn_offset, matched_off);
			x = ptree_search_m(v, t, m->rm_mask);
			while (x && x->rn_mask != m->rm_mask)
				x = x->rn_dupedkey;
			if (x && ptree_satisfies_leaf(v, x, off)){
				dprint(("ptree_matchaddr End 4\n"));
				return x;
			}
		}
		m = m->rm_mklist;
	}
	dprint(("ptree_matchaddr End 5\n"));
	return 0;
}

	struct ptree_node *
ptree_addroute(v_arg, n_arg, head, treenodes)
	void *v_arg, *n_arg;
	struct ptree *head;
	struct ptree_node treenodes[2];
{
	dprint(("ptree_addroute Start\n"));
	caddr_t v = (caddr_t)v_arg, netmask = (caddr_t)n_arg;
	register struct ptree_node *t, *x = 0, *tt;
	struct ptree_node *saved_tt, *top = head->rnh_treetop;
	short b = 0, b_leaf = 0;
	int keyduplicated;
	caddr_t mmask;
	struct ptree_mask *m, **mp;

	/*
	 * In dealing with non-contiguous masks, there may be
	 * many different routes which have the same mask.
	 * We will find it useful to have a unique pointer to
	 * the mask to speed avoiding duplicate references at
	 * nodes and possibly save time in calculating indices.
	 */
	if (netmask)  {
		if ((x = ptree_addmask(netmask, 0, top->rn_offset)) == 0){
			dprint(("ptree_addroute End 1\n"));
			return (0);
		}
		b_leaf = x->rn_bit;
		b = -1 - x->rn_bit;
		netmask = x->rn_key;
	}
	/*
	 * Deal with duplicated keys: attach node to previous instance
	 */
	saved_tt = tt = ptree_insert(v, head, &keyduplicated, treenodes);
	dprint(("ptree_addroute: keyduplicated = %d\n",keyduplicated));
	if (keyduplicated) {
		for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
			if (tt->rn_mask == netmask){
				dprint(("ptree_addroute End(keyduplicated)\n"));
				return (0);
			}
			if (netmask == 0 ||
					(tt->rn_mask &&
					 ((b_leaf < tt->rn_bit) /* index(netmask) > node */
					  || ptree_refines(netmask, tt->rn_mask)
					  || ptree_lexobetter(netmask, tt->rn_mask))))
			break;
		}
		/*
		 * If the mask is not duplicated, we wouldn't
		 * find it among possible duplicate key entries
		 * anyway, so the above test doesn't hurt.
		 *
		 * We sort the masks for a duplicated key the same way as
		 * in a masklist -- most specific to least specific.
		 * This may require the unfortunate nuisance of relocating
		 * the head of the list.
		 *
		 * We also reverse, or doubly link the list through the
		 * parent pointer.
		 */
		if (tt == saved_tt) {
			struct	ptree_node *xx = x;
			/* link in at head of list */
			(tt = treenodes)->rn_dupedkey = t;
			tt->rn_flags = t->rn_flags;
			tt->rn_parent = x = t->rn_parent;
			t->rn_parent = tt;	 		/* parent */
			if (x->rn_left == t)
				x->rn_left = tt;
			else
				x->rn_right = tt;
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
	/*
	 * Put mask in tree.
	 */
	dprint(("ptree_addroute: put netmask = %s\n",netmask));
	if (netmask) {
		dprint(("ptree_addroute: put netmask in %p\n",tt));
		tt->rn_mask = netmask;
		tt->rn_bit = x->rn_bit;
		tt->rn_flags = RNF_ACTIVE;
	}
	t = saved_tt->rn_parent;
	if(!t){
		dprint(("ptree_addroute: goto on2 if(!tt->parent)\n"));
		goto on2;
	}
	dprint(("ptree_addroute: saved_tt->rn_parent = %p\n",t));
	if (keyduplicated){
		dprint(("ptree_addroute: goto on2 if(keyduplicated)\n"));
		goto on2;
	}
	b_leaf = -1 - t->rn_bit;
	dprint(("ptree_addroute: b_leaf = %d\n",b_leaf));
	if (t->rn_right == saved_tt)
		x = t->rn_left;
	else
		x = t->rn_right;
	if(!x){
		dprint(("ptree_addroute: goto on2 if(!x)\n"));
		goto on2;
	}

	/* Promote general routes from below */
	if (x->rn_bit < 0) {
		dprint(("ptree_addroute: x->rn_bit = %d\n",x->rn_bit));
		for (mp = &saved_tt->rn_mklist; x; x = x->rn_dupedkey)
			if (x->rn_mask && (x->rn_bit >= b_leaf) && x->rn_mklist == 0) {
				*mp = m = ptree_new_mask(x, 0);
				if (m)
					mp = &m->rm_mklist;
			}
	} else if (x->rn_mklist) {
		/*
		 * Skip over masks whose index is > that of new node
		 */
		for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
			if (m->rm_bit >= b_leaf)
				break;
		t->rn_mklist = m; *mp = 0;
	}
on2:
	/* Add new route to highest possible ancestor's list */
	dprint(("ptree_addroute: add new route to highest list\n"));
	if ((netmask == 0) || (b > t->rn_bit )){
		dprint(("ptree_addroute: can't lift at all\n"));
		return tt; /* can't lift at all */
	}
	b_leaf = tt->rn_bit;
	do {
		x = t;
		t = t->rn_parent;
	} while (b <= t->rn_bit && x != top);
	/*
	 * Search through routes associated with node to
	 * insert new route according to index.
	 * Need same criteria as when sorting dupedkeys to avoid
	 * double loop on deletion.
	 */
	x = saved_tt;
	for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist) {
		if (m->rm_bit < b_leaf)
			continue;
		if (m->rm_bit > b_leaf)
			break;
		if (m->rm_flags & RNF_NORMAL) {
			mmask = m->rm_leaf->rn_mask;
			if (tt->rn_flags & RNF_NORMAL) {
				log(LOG_ERR, 
						"Non-unique normal route, mask not entered\n");
				dprint(("ptree_addroute End 3\n"));
				return tt;
			}
		} else
			mmask = m->rm_mask;
		if (mmask == netmask) {
			m->rm_refs++;
			tt->rn_mklist = m;
			dprint(("ptree_addroute End 4\n"));
			return tt;
		}
		if (ptree_refines(netmask, mmask)
				|| ptree_lexobetter(netmask, mmask))
			break;
	}

	*mp = ptree_new_mask(tt, *mp);
	dprint(("ptree_addroute End 5\n"));
	return tt;
}


	struct ptree_node *
ptree_deladdr(v_arg, netmask_arg, head)
	void *v_arg, *netmask_arg;
	struct ptree *head;
{
	dprint(("ptree_deladdr Start\n"));
	register struct ptree_node *t, *p, *x, *tt;
	struct ptree_mask *m, *saved_m, **mp;
	struct ptree_node *dupedkey, *saved_tt, *top;
	caddr_t v, netmask;
	int b, head_off, vlen;

	v = v_arg;
	netmask = netmask_arg;
	x = head->top;
	vlen =  LEN(v);
	tt = ptree_search(v, vlen, head);
	head_off = x->rn_offset;
	saved_tt = tt;
	top = x;
	if (tt == 0 || bcmp(v + head_off, tt->rn_key + head_off, vlen - head_off)){
		dprint(("ptree_deladdr End 1\n"));
		return (0);
	}
	/*
	 * Delete our route from mask lists.
	 */
	if (netmask) {
		if ((x = ptree_addmask(netmask, 1, head_off)) == 0){
			dprint(("ptree_deladdr End 2\n"));
			return (0);
		}
		netmask = x->rn_key;
		while (tt->rn_mask != netmask)
			if ((tt = tt->rn_dupedkey) == 0){
		dprint(("ptree_deladdr End 3\n"));
				return (0);
			}
	}
	if (tt->rn_mask == 0 || (saved_m = m = tt->rn_mklist) == 0)
		goto on1;
	if (tt->rn_flags & RNF_NORMAL) {
		if (m->rm_leaf != tt || m->rm_refs > 0) {
			log(LOG_ERR, "rn_delete: inconsistent annotation\n");
		dprint(("ptree_deladdr End 4\n"));
			return 0;  /* dangling ref could cause disaster */
		}
	} else {
		if (m->rm_mask != tt->rn_mask) {
			log(LOG_ERR, "rn_delete: inconsistent annotation\n");
			goto on1;
		}
		if (--m->rm_refs >= 0)
			goto on1;
	}
	b = -1 - tt->rn_bit;
	t = saved_tt->rn_parent;
	if (b > t->rn_bit)
		goto on1; /* Wasn't lifted at all */
	do {
		x = t;
		t = t->rn_parent;
	} while (b <= t->rn_bit && x != top);
	for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
		if (m == saved_m) {
			*mp = m->rm_mklist;
			MKFree(m);
			break;
		}
	if (m == 0) {
		log(LOG_ERR, "rn_delete: couldn't find our annotation\n");
		if (tt->rn_flags & RNF_NORMAL){
		dprint(("ptree_deladdr End 5\n"));
			return (0); /* Dangling ref to us */
		}
	}
on1:
	/*
	 * Eliminate us from tree
	 */
	if (tt->rn_flags & RNF_ROOT){
		dprint(("ptree_deladdr End 6\n"));
		return (0);
	}
#ifdef RN_DEBUG
	/* Get us out of the creation list */
	for (t = rn_clist; t && t->rn_ybro != tt; t = t->rn_ybro) {}
	if (t) t->rn_ybro = tt->rn_ybro;
#endif
	t = tt->rn_parent;
	dupedkey = saved_tt->rn_dupedkey;
	if (dupedkey) {
		/*
		 * Here, tt is the deletion target and
		 * saved_tt is the head of the dupekey chain.
		 */
		if (tt == saved_tt) {
			/* remove from head of chain */
			x = dupedkey; x->rn_parent = t;
			if (t->rn_left == tt)
				t->rn_left = x;
			else
				t->rn_right = x;
		} else {
			/* find node in front of tt on the chain */
			for (x = p = saved_tt; p && p->rn_dupedkey != tt;)
				p = p->rn_dupedkey;
			if (p) {
				p->rn_dupedkey = tt->rn_dupedkey;
				if (tt->rn_dupedkey)		/* parent */
					tt->rn_dupedkey->rn_parent = p;
				/* parent */
			} else log(LOG_ERR, "rn_delete: couldn't find us\n");
		}
		t = tt + 1;
		if  (t->rn_flags & RNF_ACTIVE) {
#ifndef RN_DEBUG
			*++x = *t;
			p = t->rn_parent;
#else
			b = t->rn_info;
			*++x = *t;
			t->rn_info = b;
			p = t->rn_parent;
#endif
			if (p->rn_left == t)
				p->rn_left = x;
			else
				p->rn_right = x;
			x->rn_left->rn_parent = x;
			x->rn_right->rn_parent = x;
		}
		goto out;
	}
	if (t->rn_left == tt)
		x = t->rn_right;
	else
		x = t->rn_left;
	p = t->rn_parent;
	if (p->rn_right == t)
		p->rn_right = x;
	else
		p->rn_left = x;
	x->rn_parent = p;
	/*
	 * Demote routes attached to us.
	 */
	if (t->rn_mklist) {
		if (x->rn_bit >= 0) {
			for (mp = &x->rn_mklist; (m = *mp);)
				mp = &m->rm_mklist;
			*mp = t->rn_mklist;
		} else {
			/* If there are any key,mask pairs in a sibling
			   duped-key chain, some subset will appear sorted
			   in the same order attached to our mklist */
			for (m = t->rn_mklist; m && x; x = x->rn_dupedkey)
				if (m == x->rn_mklist) {
					struct ptree_mask *mm = m->rm_mklist;
					x->rn_mklist = 0;
					if (--(m->rm_refs) < 0)
						MKFree(m);
					m = mm;
				}
			if (m)
				log(LOG_ERR,
						"rn_delete: Orphaned Mask %p at %p\n",
						(void *)m, (void *)x);
		}
	}
	/*
	 * We may be holding an active internal node in the tree.
	 */
	x = tt + 1;
	if (t != x) {
#ifndef RN_DEBUG
		*t = *x;
#else
		b = t->rn_info;
		*t = *x;
		t->rn_info = b;
#endif
		t->rn_left->rn_parent = t;
		t->rn_right->rn_parent = t;
		p = x->rn_parent;
		if (p->rn_left == x)
			p->rn_left = t;
		else
			p->rn_right = t;
	}
out:
	tt->rn_flags &= ~RNF_ACTIVE;
	tt[1].rn_flags &= ~RNF_ACTIVE;
	dprint(("ptree_deladdr End 7\n"));
	return (tt);
}

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
	dprint(("ptree_walktree_from Start\n"));
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
		printf("node %p (%d)\n", rn, rn->rn_bit);
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
	dprint(("ptree_walktree_from End\n"));
	return 0;
}


	static int
ptree_walktree(h, f, w)
	struct ptree *h;
	walktree_f_t *f;
	void *w;
{
	dprint(("ptree_walktree Start\n"));
	struct ptree_node *base, *next;
	register struct ptree_node *rn = h->rnh_treetop;

	for (;;) {
		base = rn;
		next = ptree_next(base);
		dprint(("ptree_walktree: base %p next %p\n",base,next));
		if( !next ){
			dprint(("ptree_walktree End 1\n"));
			return (0);
		}
		rn = next;
	}
	/* NOTREACHED */
	dprint(("ptree_walktree End 2\n"));
}

	int
ptree_inithead(head, off)
	void **head;
	int off;
{
	dprint(("ptree_inithead Start\n"));
	register struct ptree *rnh;
	register struct ptree_node *t;
	int *data = NULL;
	*data = 1;
	
	if (*head){
		dprint(("ptree_inithead End 1\n"));
		return (1);
	}
	R_Zalloc(rnh, struct ptree *, sizeof (*rnh));
	if (rnh == 0){
		dprint(("ptree_inithead End 2\n"));
		return (0);
	}
#ifdef _KERNEL
	RADIX_NODE_HEAD_LOCK_INIT(rnh);
#endif
	*head = rnh;
	t = ptree_add(rn_zeros,off,data,rnh);
	t->keylen = (int)LEN(rn_zeros);
	dprint(("ptree_inithead: head_node_len = %d\n",t->keylen));
	t->rn_flags = RNF_ROOT | RNF_ACTIVE;
#ifdef PTREE_MPATH
	rnh->rnh_multipath = 1;
#endif
	rnh->rnh_addaddr = ptree_addroute;
	rnh->rnh_deladdr = ptree_deladdr;
	rnh->rnh_matchaddr = ptree_matchaddr;
	rnh->rnh_lookup = ptree_lookup;
	rnh->rnh_walktree = ptree_walktree;
	rnh->rnh_walktree_from = ptree_walktree_from;
	rnh->top = t;
	dprint(("ptree_inithead: rnh->top->rn_falgs = %d\n",rnh->top->rn_flags));
	dprint(("ptree_inithead End 3\n"));
	return (1);
}

	void
ptree_init()
{
	dprint(("ptree_init Start\n"));
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
		dprint(("ptree_init End 1\n"));
		return;
	}
	R_Malloc(rn_zeros, char *, 3 * max_keylen);
	if (rn_zeros == NULL) 
		panic("ptree_init");
	bzero(rn_zeros, 3 * max_keylen);
	rn_ones = cp = rn_zeros + max_keylen;
	addmask_key = cplim = rn_ones + max_keylen;
	while (cp < cplim)
		*cp++ = -1;
	if (ptree_inithead((void **)(void *)&mask_rnhead, 0) == 0)
		panic("ptree_init 2");

	dprint(("ptree_init End 2\n"));
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
	uint32_t i = 0;
	struct rtentry *rt;
	rt = (struct rtentry *)rn;
	/* count mlist */
	while (rt != NULL) {
		if(rt->mlist[i]!=NULL)
			i += rt->rt_rmx.rmx_weight;
	}
	return (i);
}

	struct rtentry *
rt_mpath_matchgate(struct rtentry *rt, struct sockaddr *gate)
{
	uint32_t	i = 0;
	struct ptree_node *rn;
	struct rtentry	*match;

	if (!rt->mlist)
		return rt;

	if (!gate)
		return NULL;

	/* beyond here, we use rn as the master copy */
	rn = (struct ptree_node *)rt;
	do {
		match = rt->mlist[i];
		/*
		 * we are removing an address alias that has 
		 * the same prefix as another address
		 * we need to compare the interface address because
		 * rt_gateway is a special sockadd_dl structure
		 */
		if (match->rt_gateway->sa_family == AF_LINK) {
			if (!memcmp(match->rt_ifa->ifa_addr, gate, gate->sa_len))
				break;
		} else {
			if (match->rt_gateway->sa_len == gate->sa_len &&
					!memcmp(match->rt_gateway, gate, gate->sa_len))
				break;
		}
	} while (rt->mlist[i] != NULL);

	return (struct rtentry *)match;
}

/* 
 * go through the chain and unlink "rt" from the list
 * the caller will free "rt"
 */
static uint32_t hashjitter;

	int
rt_mpath_delete(struct rtentry *headrt, struct rtentry *rt)
{
	uint32_t i = 0, n;
	struct rtentry *t;

	if (!headrt || !rt)
		return (0);

	n = ptree_mpath_count((struct ptree_node *)headrt);
	t = headrt->mlist[i];
	while (t) {
		if (t == rt) {
			t->mlist[i] = t->mlist[n-1];
			t->mlist[n-1] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * check if we have the same key/mask/gateway on the table already.
 */
	int
rt_mpath_conflict(struct ptree *rnh, struct rtentry *rt,
		struct sockaddr *netmask)
{
	struct ptree_node *rn;
	struct rtentry *rt1;
	char *p, *q, *eq;
	int same, l, skip;
	uint32_t i;

	rn = rnh->rnh_lookup(rt_key(rt), netmask, (int)LEN(rt_key(rt)), rnh);
	if (!rn || rn->rn_flags & RNF_ROOT)
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
	i = 0;
	rt1 = rt->mlist[i];
	/* key/mask were the same.  compare gateway for all multipaths */
	do {
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
	} while ((rt1 = rt->mlist[++i]) != NULL);

different:
	return 0;
}

	void
rtalloc_mpath_fib(struct route *ro, uint32_t hash, u_int fibnum)
{
	u_int32_t n;
	struct rtentry *rt, *rt0;

	/*
	 * XXX we don't attempt to lookup cached route again; what should
	 * be done for sendto(3) case?
	 */
	if (ro->ro_rt && ro->ro_rt->rt_ifp && (ro->ro_rt->rt_flags & RTF_UP))
		return;				 
	ro->ro_rt = rtalloc1_fib(&ro->ro_dst, 1, 0, fibnum);

	/* if the route does not exist or it is not multipath, don't care */
	if (ro->ro_rt == NULL)
		return;
	if (ro->ro_rt->mlist == NULL) {
		RT_UNLOCK(ro->ro_rt);
		return;
	}

	/* beyond here, we use rn as the master copy */
	rt0 = ro->ro_rt;
	n = ptree_mpath_count((struct ptree_node *)rt0);

	/* gw selection by Modulo-N Hash (RFC2991) XXX need improvement? */
	hash += hashjitter;
	hash %= n;
	rt = rt0->mlist[n];

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
