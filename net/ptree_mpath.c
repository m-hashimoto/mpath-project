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

#ifdef DEBUG
#include <sys/types.h>
#include <netinet/in.h>

static int
debug_node_print(struct ptree_node *rn)
{
	register unsigned char *ip;
			
	printf("/*-------------------------*/\n");
	printf("node = %p\n",rn);
	printf("mklist = %p\n",rn->rn_mklist);
	if( rn->rn_key ){
		ip = (unsigned char *)rn->rn_key;
		printf("key %d.%d.%d.%d: ",*ip,*ip+1,*ip+2,*ip+3);
	}
	if( rn->rn_mask ){
		ip = (unsigned char *)rn->rn_mask;
		printf("mask %d.%d.%d.%d: ",*ip,*ip+1,*ip+2,*ip+3);
	}
	if( rn->keylen ) printf("keylen %d\n",rn->keylen);
	if( rn->rn_bit ) printf("rn_bit %d ",rn->rn_bit);
	if( rn->rn_bmask ) printf("rn_bmask 0x%x ",rn->rn_bmask);
	if( rn->rn_flags ) printf("flag 0x%x\n",rn->rn_flags);
	printf("parent = %p\n",rn->parent);
	printf("left = %p, right = %p\n",rn->rn_left,rn->rn_right);
	printf("/*-------------------------*/\n");
	return 0;
}
#endif /* DEBUG */
	
#define MKGet(m) {                                              \
	if (rn_mkfreelist) {                                    \
		m = rn_mkfreelist;                              \
		rn_mkfreelist = (m)->rm_mklist;                 \
	} else                                                  \
	R_Malloc(m, struct ptree_mask *, sizeof (struct ptree_mask)); }

#define MKFree(m) { (m)->rm_mklist = rn_mkfreelist; rn_mkfreelist = (m);}
#define LEN(x) (*(const u_char *)(x))
#define rn_masktop (mask_rnhead->rnh_treetop)
#if 0
static struct ptree_node *ptree_search_m(void *v_arg,
	       	struct ptree_node *head, void *m_arg);
#endif
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
	caddr_t v = v_arg;
	register caddr_t cp;
	int vlen = (int)LEN(v);
	register int b;
	dprint(("-ptree_insert Start\n"));
	dprint(("-ptree_insert: v = %p vlen = %d head = %p\n",v,vlen,head));
	struct ptree_node *top = head->rnh_treetop, *tt;
	
	if (!top){
		dprint(("-ptree_insert: top = NULL\n"));
		goto on2;
	}
	
	int head_off = top->rn_offset;
	register struct ptree_node *t = ptree_search(v, vlen, head);
	cp = v + head_off;
	
	if(!t){
		dprint(("-ptree_insert: search(v) = NULL\n"));
		b = -1 - vlen;
		goto on2;
	}
	/* Find first bit at which v and t->rn_key differ */ 
	{         
		register caddr_t cp2 = t->rn_key + head_off;  
		register int cmp_res;
		caddr_t cplim = v + vlen;
		
		dprint(("-ptree_insert: "));
		while (cp < cplim){
			dprint((" +"));
			if (*cp2++ != *cp++){
				dprint(("goto on1\n"));
				goto on1;
			}
		}
		dprint(("key dupentry\n"));
		*dupentry = 1;  
		return t;
on1:
		dprint(("-ptree_insert: on1\n"));
		cmp_res = (cp[-1] ^ cp2[-1]) & 0xff;  
		for (b = (cp - v) << 3; cmp_res; b--) 
			cmp_res >>= 1;
		dprint(("-ptree_insert: first different bit = 0x%x\n",b));
on2:
		*dupentry = 0;
	}
	{
		//register struct ptree_node *p, *x = top;
		int *data;
		data = &vlen;
		dprint(("-ptree_insert: data = 0x%x\n",*data));
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
		tt = ptree_add(v_arg, vlen, data, head, nodes);
		tt->rn_bit = - 1 - tt->keylen;
#ifdef RN_DEBUG
		if (rn_debug)
			log(LOG_DEBUG, "rn_insert: Coming Out:\n"), traverse(p);
#endif
	}
	dprint(("-ptree_insert End: insert node = %p\n",nodes));
	return (tt);
}

	struct ptree_node *
ptree_addmask(n_arg, search, skip)        
	int search, skip;
	void *n_arg;
{
	dprint(("-ptree_addmask Start\n"));
	caddr_t netmask = (caddr_t)n_arg;
	register struct ptree_node *x;
	register caddr_t cp, cplim;
	register int b = 0, mlen, j;
	int maskduplicated, m0, isnormal;
	struct ptree_node *saved_x;  
	static int last_zeroed = 0;  
	
	dprint(("-ptree_addmask: search = %d, skip = %d, netmask = %p\n",search,skip,netmask));
	
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
		dprint(("-ptree_addmask End if(mlen<=skip)\n"));
		return (mask_rnhead->rnh_nodes); 
	}     
	
	if (m0 < last_zeroed)  
		bzero(addmask_key + m0, last_zeroed - m0); 
	
	*addmask_key = last_zeroed = mlen;
	dprint(("-ptree_addmask: mask_rnhead = %p\n",mask_rnhead));
	x = ptree_search(addmask_key, mlen, mask_rnhead);
	
	if(!x){
		dprint(("-ptree_addmask: search result is NULL\n"));
		goto on1;
	}
	dprint(("-ptree_addmask: addmask_key = %p x = %p mlen = 0x%x\n",
							addmask_key,x,mlen));
	if(x) dprint(("x->rn_key = %p\n",x->key));
	
	if (!x->rn_key || memcmp(addmask_key, x->rn_key, mlen))  
		x = 0;
	if (x || search){
		dprint(("-ptree_addmask End if(x||search)\n"));
		return (x);
	}

on1:
	R_Zalloc(x, struct ptree_node *, max_keylen + 2 * sizeof (*x));
	if ((saved_x = x) == 0){
		dprint(("-ptree_addmask End if(saved_x==0)\n"));
		return (0);
	}
	netmask = cp = (caddr_t)(x + 2);
	bcopy(addmask_key, cp, mlen);
	x = ptree_insert(cp, mask_rnhead, &maskduplicated, x);
	if (maskduplicated) { 
		log(LOG_ERR, "rn_addmask: mask impossibly already in tree");
		Free(saved_x);
		dprint(("-ptree_addmask End if(maskduplicated)\n"));
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
	x->rn_bit = -1 - b;
	//x->rn_bit = b - 1;
	dprint(("-ptree_addmask: x->rn_bit = 0x%x\n",x->rn_bit));
	if (isnormal){
		x->rn_flags |= RNF_NORMAL;
		dprint(("-ptree_addmask: RNF_NORMAL flag ON\n"));
	}
	
	dprint(("-ptree_addmask End\n"));
	return (x);
}


/*
 * Same as above, but with an additional mask.
 * XXX note this function is used only once.
 */
#if 0
	static struct ptree_node *
ptree_search_m(v_arg, head, m_arg)
	struct ptree_node *head;
	void *v_arg, *m_arg;
{
	dprint(("-ptree_seach_m Start\n"));
	dprint(("-ptree_search_m: v_arg = %p, head = %p, m_arg = %p\n",v_arg,head,m_arg));
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
	dprint(("-ptree_seach_m End\n"));
	return x;
}
#endif
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

	static int      
ptree_lexobetter(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	dprint(("-ptree_lexobetter Start\n"));
	register u_char *mp = m_arg, *np = n_arg, *lim;

	if (LEN(mp) > LEN(np)){	
		dprint(("-ptree_lexobetter End: return 1\n"));
		return 1;
	}
      	/* not really, but need to check longer one first */   
	if (LEN(mp) == LEN(np))
		for (lim = mp + LEN(mp); mp < lim;)
			if (*mp++ > *np++){
				dprint(("-ptree_lexobetter End: return 1\n"));
				return 1;
			}
	dprint(("-ptree_lexobetter End: return 0\n"));
	return 0;
}

	static struct ptree_mask *
ptree_new_mask(tt, next)
	register struct ptree_node *tt; 
	register struct ptree_mask *next;
{
	dprint(("-ptree_new_mask Start\n"));
	dprint(("-ptree_new_mask: tt = %p next = %p\n",tt,next));
	register struct ptree_mask *m;

	MKGet(m);
	if (m == 0) {
		log(LOG_ERR, "Mask for route not entered\n");
		dprint(("-ptree_new_mask End: if(m == 0)\n"));
		return (0);
	}
	bzero(m, sizeof *m);
	m->rm_bit = tt->rn_bit;
	m->rm_flags = tt->rn_flags | RNF_NORMAL;
	dprint(("-ptree_new_mask: m->rm_bit = 0x%x m->rm_flags = 0x%x\n",
							m->rm_bit,m->rm_flags));
	m->rm_leaf = tt;
	m->rm_mask = tt->rn_mask;
	dprint(("-ptree_new_mask: m->rm_leaf = %p m->rm_mask = %p\n",
							m->rm_leaf,m->rm_mask));
	m->rm_mklist = next;
	tt->rn_mklist = m;
	dprint(("-ptree_new_mask End\n"));
	return m;
}

	static int
ptree_satisfies_leaf(trial, leaf, skip)
	char *trial;
	register struct ptree_node *leaf;
	int skip;
{
	dprint(("-ptree_satisfines_leaf Start\n"));
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
			dprint(("-ptree_satisfines_leaf End: cp and cp2 is diff\n"));
			return 0;
		}
	dprint(("-ptree_satisfines_leaf End\n"));
	return 1;
}

	struct ptree_node *
ptree_matchaddr(v_arg, head)
	void *v_arg;
	struct ptree *head;
{
	dprint(("-ptree_matchaddr Start\n"));
	caddr_t v = v_arg;
	register struct ptree_node *t = head->top;
	if(!t){
		dprint(("-ptree_matchaddr: top = NULL\n"));
		goto miss;
	}
	
	register caddr_t cp = v, cp2;
	caddr_t cplim;
	struct ptree_node *saved_t;
	int off = t->rn_offset, vlen = LEN(cp), matched_off;
	register int test, b, rn_bit;

	dprint(("-ptree_matchaddr: v = %p vlen = %d head = %p top = %p\n",
							v,vlen,head,t));
	t = saved_t = ptree_search(v, vlen, head);
	if( !saved_t ){
		dprint(("-ptree_matchaddr: search result is NULL\n"));
		goto miss;
	}
	if (t->rn_mask){
		vlen = *(u_char *)t->rn_mask;
		dprint(("-ptree_matchaddr: if(t->rn_mask) vlen = %d\n",vlen));
	}

	cp += off; cp2 = t->rn_key + off; cplim = v + vlen;
	dprint(("-ptree_matchaddr:"));
	for (; cp < cplim; cp++, cp2++){
		dprint((" +"));	
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
					dprint(("-ptree_matchaddr: rn_bit = 0x%x rm_bit = 0x%x\n",rn_bit,m->rm_bit));
					if (rn_bit <= m->rm_bit)
							return (m->rm_leaf);
			}
#if 0
			else {
					off = min(t->rn_offset, matched_off);
					dprint(("-ptree_matchaddr: off = %d\n",off));
					x = ptree_search_m(v, t, m->rm_mask);
					while (x && x->rn_mask != m->rm_mask)
							x = x->rn_dupedkey;
					if (x && ptree_satisfies_leaf(v, x, off)){
							dprint(("-ptree_matchaddr End: return x\n"));
							return x;
					}
			}
#endif
			m = m->rm_mklist;
			dprint(("-ptree_matchaddr: next rm_mklist = %p\n",m));
	}

miss:
	dprint(("-ptree_matchaddr End: miss\n"));
	return 0;
}

		struct ptree_node *
ptree_addroute(v_arg, n_arg, head, treenodes)
		void *v_arg, *n_arg;
		struct ptree *head;
		struct ptree_node treenodes[2];
{
		dprint(("-ptree_addroute Start\n"));
		caddr_t v = (caddr_t)v_arg, netmask = (caddr_t)n_arg;
		register struct ptree_node *t, *x = 0, *tt;
		struct ptree_node *saved_tt, *top = head->rnh_treetop;
		short b = 0, b_leaf = 0;
		int keyduplicated;
		caddr_t mmask;
		struct ptree_mask *m, **mp = 0;
		dprint(("-ptree_addroute: key = %p\n",v));

		if (netmask)  {
				if ((x = ptree_addmask(netmask, 0, top->rn_offset)) == 0){
						dprint(("-ptree_addroute End 1\n"));
						return (0);
				}
				b_leaf = x->rn_bit;
				b = -1 - x->rn_bit;
				netmask = x->rn_key;
				dprint(("-ptree_addroute: set netmask\n"));
		}
		/*
		 * Deal with duplicated keys: attach node to previous instance
		 */
		saved_tt = tt = ptree_insert(v_arg, head, &keyduplicated, treenodes);
		dprint(("-ptree_addroute: tt = %p nodes = %p\n",tt,treenodes));
		dprint(("-ptree_addroute: keyduplicated = %d\n",keyduplicated));
		if (keyduplicated) {
				for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
						if (tt->rn_mask == netmask){
								dprint(("-ptree_addroute End(keyduplicated)\n"));
								return (0);
						}
						if (netmask == 0 ||
										(tt->rn_mask &&
										 ((b_leaf < tt->rn_bit) /* index(netmask) > node */
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
		dprint(("-ptree_addroute: netmask = %p\n",netmask));
		if (netmask) {
				dprint(("-ptree_addroute: put netmask in %p\n",tt));
				tt->rn_mask = netmask;
				tt->rn_bit = x->rn_bit;
				tt->rn_flags |= x->rn_flags & RNF_ACTIVE;
		}

		t = saved_tt;
		if (keyduplicated){
				dprint(("-ptree_addroute: goto on2 if(keyduplicated)\n"));
				goto on2;
		}
		b_leaf = -1 - t->rn_bit;
		dprint(("-ptree_addroute: b_leaf = %d\n",b_leaf));
		if(t->rn_bit < 0){
				for(mp = &t->rn_mklist;t;t=t->rn_dupedkey)
					if(t->rn_mask && (t->rn_bit >= b_leaf) && t->rn_mklist == 0){
							*mp = m = ptree_new_mask(t,0);
							dprint(("-ptree_addroute: m = %p\n",m));
							if (m)
									mp = &m->rm_mklist;
				}
		} else if(t->rn_mklist){
				/*
				 * Skip over masks whos index is > that of new node
				 */
				for(mp = &t->rn_mklist;(m = *mp);mp = &m->rm_mklist)
						if(m->rm_bit >= b_leaf)
								break;
				t->rn_mklist = m; *mp = 0;
		}
on2:
		dprint(("-ptree_addroute: on2\n"));
		dprint(("-ptree_addroute: on2 t=%p tt=%p\n",t,tt));
		if((netmask == 0) || (b > t->rn_bit) )
				return tt;
		b_leaf = tt->rn_bit;
		dprint(("-ptree_addroute: on2 b_leaf = %d\n",b_leaf));
		do {
				x = t;
				t = t->rn_parent;
				dprint(("-ptree_addroute: on2 x = %p\n",x));
		} while (b <= t->rn_bit );
		for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist) {
				dprint(("-ptree_addroute: on2 test 1\n"));
				if (m->rm_bit < b_leaf)
						continue;
				if (m->rm_bit > b_leaf)
						break;
				if (m->rm_flags & RNF_NORMAL) {
						dprint(("-ptree_addroute: on2 test 2\n"));
						mmask = m->rm_leaf->rn_mask;
						if (tt->rn_flags & RNF_NORMAL) {
								log(LOG_ERR,
								"Non-unique normal route, mask not entered\n");
								return tt;
						}
				} else
						mmask = m->rm_mask;
				if (mmask == netmask) {
						dprint(("-ptree_addroute: on2 test 3\n"));
						m->rm_refs++;
						tt->rn_mklist = m;
						return tt;
				}
				if (ptree_refines(netmask, mmask)
								|| ptree_lexobetter(netmask, mmask))
						break;
		}

		*mp = ptree_new_mask(tt, *mp);
		debug_node_print(tt);
		dprint(("-ptree_addroute End\n"));
		return tt;
}


		struct ptree_node *
ptree_deladdr(v_arg, netmask_arg, head)
		void *v_arg, *netmask_arg;
		struct ptree *head;
{
		dprint(("-ptree_deladdr Start\n"));
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
				dprint(("-ptree_deladdr End1: return 0\n"));
				return (0);
		}
		/*
		 * Delete our route from mask lists.
		 */
		if (netmask) {
				if ((x = ptree_addmask(netmask, 1, head_off)) == 0){
						dprint(("-ptree_deladdr End2: return 0\n"));
						return (0);
				}
				netmask = x->rn_key;
				while (tt->rn_mask != netmask)
						if ((tt = tt->rn_dupedkey) == 0){
								dprint(("-ptree_deladdr End3: return 0\n"));
								return (0);
						}
		}
		if (tt->rn_mask == 0 || (saved_m = m = tt->rn_mklist) == 0)
				goto on1;
		if (tt->rn_flags & RNF_NORMAL) {
				if (m->rm_leaf != tt || m->rm_refs > 0) {
						log(LOG_ERR, "rn_delete: inconsistent annotation\n");
						dprint(("-ptree_deladdr End4: return 0\n"));
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
						dprint(("-ptree_deladdr End5: return 0\n"));
						return (0); /* Dangling ref to us */
				}
		}
on1:
		/*
		 * Eliminate us from tree
		 */
		if (tt->rn_flags & RNF_ROOT){
				dprint(("-ptree_deladdr End6: return 0\n"));
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
		dprint(("-ptree_deladdr End\n"));
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


		static int
ptree_walktree(h, f, w)
		struct ptree *h;
		walktree_f_t *f;
		void *w;
{
		dprint(("-ptree_walktree Start\n"));
		struct ptree_node *base, *next;
		register struct ptree_node *rn = h->rnh_treetop;
		if (!rn){
				dprint(("-ptree_walktree End (treetop = NULL)\n"));
				return (0);
		}

		//dprint(("-ptree_walktree:  top = %p keylen = 0x%x\n",rn->key,rn->keylen));
		for (;;) {
				base = rn;
				next = ptree_next(base);
				if( !next ){
						dprint(("-ptree_walktree End (next == NULL)\n"));
						//return (0);
						break;
				}
				rn = next;
				//dprint(("-ptree_walktree: next = %p keylen = 0x%x\n",rn->key,rn->keylen));
		}
		/* NOTREACHED */
#ifdef DEBUG
		/* INET tree check */
		{
				printf("INET4 ptree_walktree\n");
				register struct ptree *rnh;

				rnh = rt_tables_get_rnh(0, AF_INET);
				rn = rnh->rnh_treetop;
				for (;;) {
						debug_node_print(rn);
						base = rn;
						next = ptree_next(base);
						if( !next ){
								dprint(("-ptree_walktree End (next == NULL)\n"));
								return (0);
						}
						rn = next;
				}
		}
#endif
		dprint(("-ptree_walktree End\n"));
}

		int
ptree_inithead(head, off)
		void **head;
		int off;
{
		dprint(("-ptree_inithead Start\n"));
		register struct ptree *rnh;
		register struct ptree_node *t;
		//int *data = NULL;

		if (*head){
				dprint(("-ptree_inithead End1\n"));
				return (1);
		}
		R_Zalloc(rnh, struct ptree *, sizeof (*rnh));
		if (rnh == 0){
				dprint(("-ptree_inithead End2\n"));
				return (0);
		}
#ifdef _KERNEL
		RADIX_NODE_HEAD_LOCK_INIT(rnh);
#endif
		*head = rnh;
		t = NULL;
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
