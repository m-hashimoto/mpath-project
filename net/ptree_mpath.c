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

#include <sys/types.h>
#include <netinet/in.h>

#include <rpc/rpc.h>
#include <rpc/nettype.h>
#include <rpc/rpc_com.h>

 void
sprint_inet_ntoa(int af, void *sa)
{
	//dprint(("-sprint_inet_ntoa: af[%d] sa[%p]\n",af,sa));
	if(af == AF_INET){
		char str[INET_ADDRSTRLEN];
		__rpc_inet_ntop(AF_INET, &((struct sockaddr_in *)sa)->sin_addr, str, INET_ADDRSTRLEN);
		printf("%s",str);
	} else if(af == AF_INET6) {
		char str[INET6_ADDRSTRLEN];
		__rpc_inet_ntop(AF_INET6, &((struct sockaddr_in6 *)sa)->sin6_addr, str, INET6_ADDRSTRLEN);
		printf("%s",str);
	}
}

	int
debug_node_print(struct ptree_node *pn, int offset)
{
	if(!pn->key || !pn->keylen){
		dprint(("-debug_node_print: pn[%p] pn->key[%p]\n",pn,pn->key));
		dprint(("-debug_node_print: pn->parent[%p] pn->left[%p] pn->rigth[%p]\n",
														pn->parent,pn->child[0],pn->child[1]));
		return 1;
	}
	if(offset == 8){ /* IPv6 */
		printf("[%p] ",pn);
		sprint_inet_ntoa(AF_INET6,pn->key);
		printf("/%3d ",pn->keylen-8*offset);
	} else { /* IPv4 */
		printf("[%p] ",pn);
		sprint_inet_ntoa(AF_INET,pn->key);
		printf("/%3d ",pn->keylen-8*offset);
	}
	printf("data[%p] <%p, %p>\n",pn->data,pn->child[0],pn->child[1]);
#ifdef PTREE_MPATH
	if(pn->data){
		struct rtentry *rt, *rt0 = pn->data;
		struct rtentry **mrt = rt0->mpath_array;
	
		printf("%12s ","gateway");
		if(offset == 8){
			sprint_inet_ntoa(AF_INET6,rt0->rt_gateway);
			printf(" flags[0x%x]\n",rt0->rt_flags);
		} else {
			sprint_inet_ntoa(AF_INET,rt0->rt_gateway);
			printf(" flags[0x%x]\n",rt0->rt_flags);
		}

		while(mrt){
			printf("mrt[%p]\n",mrt);
			rt = *mrt;	
			if(offset == 8){
				printf("%13s","+");
				sprint_inet_ntoa(AF_INET6,rt->rt_gateway);
				printf(" flags[0x%x]\n",rt->rt_flags);
			} else {
				printf("%13s","+");
				sprint_inet_ntoa(AF_INET,rt->rt_gateway);
				printf(" flags[0x%x]\n",rt->rt_flags);
			}
			mrt++;
		}
	}
#endif
	return 0;
}

	int
debug_tree_print(struct ptree_node_head *pnh)
{
		register struct ptree_node *pn, *next;
		if ( !pnh || !pnh->pnh_treetop )
			    return (0);
		pn = pnh->pnh_top;
		printf("\n pnh[%p] phn_top[%p] offset[%d]\n",pnh,pn,pnh->pnh_offset);
		printf("----------------------------------------------------------\n");
		if(!pn)
			return (0);
		for (;;) {
			if(debug_node_print(pn, pnh->pnh_offset)){
				printf("error: debug_node_print\n");
				return (1);
			}
			next = ptree_next(pn);
			if( !next )
				break;
			pn = next;
		}
		/* NOTREACHED */
		printf("----------------------------------------------------------\n\n");
		return (0);
}

static int  max_keylen;
static char *pn_zeros, *pn_ones;
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
	//caddr_t v = v_arg, m = m_arg;
	//register caddr_t cp;
	char *v = v_arg, *m = m_arg;
	register char *cp;
	struct ptree_node *top = head->pnh_top, *t, *tt;
	int len = 8*LEN(v);
	
#ifdef DEBUG
	if(head->pnh_offset == 4){
		printf("-ptree_insert: addr ");
		sprint_inet_ntoa(AF_INET, v);
		printf("/%d\n",len);
	} else {
		printf("-ptree_insert: addr ");
		sprint_inet_ntoa(AF_INET6, v);
		printf("/%d\n",len);
	}
#endif
	if(m && (LEN(m) > head->pnh_offset)){
		dprint(("-ptree_insert: LEN(m)=%d\n",LEN(m)));
		unsigned char bitmask = 0xff;
		len = head->pnh_offset;
		while(m[len] & bitmask)
			len++;
		len = 8*len;
#ifdef DEBUG
		if(head->pnh_offset == 4){
			printf("-ptree_insert: mask ");
			sprint_inet_ntoa(AF_INET, m);
			printf("/%d\n",len);
		} else {
			printf("-ptree_insert: mask ");
			sprint_inet_ntoa(AF_INET6, m);
			printf("/%d\n",len);
		}
#endif
	}
	if (!top){
		dprint(("-ptree_insert: top is NULL\n"));
		goto on1;
	}
	t = ptree_search(v, len, head->pnh_treetop);
	if (!t)
		goto on1;
	cp = v;
	{
		//register caddr_t cp2 = t->key;
		//caddr_t cplim = v;
		register char *cp2 = t->key;
		char *cplim = v;
		if ( !memcmp(cp2,cplim,len) ){
			*dupentry = 1;
			return t;
		}
	}
on1:
	*dupentry = 0;
	//{
		int *data = NULL;
		tt = ptree_add(v, len, data, head->pnh_treetop);
	//}
	dprint(("-ptree_insert End: insert tt[%p]\n",tt));
	return (tt);
}


	int
ptree_refines(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	//register caddr_t m = m_arg, n = n_arg;
	//register caddr_t lim, lim2 = lim = n + LEN(n);
	register char *m = m_arg, *n = n_arg;
	register char *lim, *lim2 = lim = n + LEN(n);
	int longer = LEN(n++) - (int)LEN(m++);
	int masks_are_equal = 1;
	dprint(("-ptree_refines Start\n"));

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
	//caddr_t v = v_arg;
	char *v = v_arg;
	register struct ptree_node *t = head->pnh_top;
	if(!t){
		dprint(("-ptree_matchaddr: top = NULL\n"));
		return 0;
	}
	
	//register caddr_t cp;
	//caddr_t cplim;
	register char *cp;
	char *cplim;
	struct ptree_node *saved_t;
	int vlen;
	
	vlen = (int)8*LEN(v);
#ifdef DEBUG
		if(head->pnh_offset == 4){
			printf("-ptree_matchaddr: addr ");
			sprint_inet_ntoa(AF_INET, v);
			printf("/%d\n",vlen);
		} else {
			printf("-ptree_matchaddr: addr ");
			sprint_inet_ntoa(AF_INET6, v);
			printf("/%d\n",vlen);
		}
#endif
	t = saved_t = ptree_search(v, vlen, head->pnh_treetop);
	if( !saved_t ){
		dprint(("-ptree_matchaddr: not match\n"));
		return 0;
	}

	cp = t->key; cplim = v; vlen = t->keylen;
#ifdef DEBUG
		if(head->pnh_offset == 4){
			printf("-ptree_matchaddr: save_t ");
			sprint_inet_ntoa(AF_INET, cp);
			printf("/%d\n",vlen);
		}else{
			printf("-ptree_matchaddr: save_t ");
			sprint_inet_ntoa(AF_INET6, cp);
			printf("/%d\n",vlen);
		}
#endif
	dprint(("-ptree_matchaddr: memcmp(cp,cplim,vlen/8)=[%d]\n",memcmp(cp,cplim,vlen/8)));
	if ( memcmp(cp,cplim,vlen/8) != 0 )
		return 0;
	dprint(("-ptree_matchaddr: match exactly as a host\n"));
	/*
	 * match exactly as a host.
	 */
	dprint(("-ptree_matchaddr End: return t[%p]\n",t));
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
#ifdef PTREE_MPATH /* multi path */
		if (keyduplicated) {
			int n;
			struct rtentry *rt0, *rt, **rt_array;
				
			rt = (struct rtentry *)rt_node;
			rt0 = tt->data;
			dprint(("-ptree_addroute: rt0[%p] rt[%p]\n",rt0,rt));
			n = ptree_mpath_count(rt0);
			rt_array = rt0->mpath_array;
			rt_array[n] = rt;
		}
#endif /* mluti path */
		return tt;
}


		struct ptree_node *
ptree_deladdr(v_arg, gate_arg, head)
		void *v_arg, *gate_arg;
		struct ptree_node_head *head;
{
		register struct ptree_node *tt;
		struct ptree_node *saved_tt, *top;
		//caddr_t v;
		char *v;
		struct sockaddr *gate;
		unsigned int len;
		dprint(("-ptree_deladdr Start: pnh[%p]\n",head));

		v = v_arg;
		gate = gate_arg;
		//netmask = netmask_arg;
		top = head->pnh_top;
		len = (int)8*LEN(v);

#ifdef DEBUG
		if(head->pnh_offset == 4){
			printf("-ptree_deladdr: addr[%p] ",v);
			sprint_inet_ntoa(AF_INET, v);
			printf("/%d\n",len);
		} else {
			printf("-ptree_deladdr: addr[%p] ",v);
			sprint_inet_ntoa(AF_INET6, v);
			printf("/%d\n",len);
		}
#endif
		
		tt = saved_tt = ptree_search(v, len, head->pnh_treetop);

		if (!saved_tt){
				dprint(("-ptree_deladdr End: ptree_node nothing\n"));
				return (0);
		}
		//register caddr_t cp, cplim;
		register char *cp, *cplim;
		cp = tt->key; cplim = v; len = tt->keylen;
#if 0
		if(netmask && (LEN(netmask) > head->pnh_offset)){
			unsigned char bitmask = 0xff;
			len = head->pnh_offset;
			while(netmask[len] == bitmask)
				len++;
			len = 8*len;
		}
#endif
#ifdef DEBUG
		if(head->pnh_offset == 4){
			printf("-ptree_deladdr: match ");
			sprint_inet_ntoa(AF_INET, cp);
			printf("/%d\n",len);
		} else {
			printf("-ptree_deladdr: match ");
			sprint_inet_ntoa(AF_INET6, cp);
			printf("/%d\n",len);
		}
#endif
		dprint(("-ptree_deladdr: memcmp(%p,%p,%d)[%d]\n",
								cp,v,len/8,memcmp(cp,v,len/8)));
		if ( memcmp(cp, v, len/8) != 0 ){
				dprint(("-ptree_deladdr End: not match\n"));
				return (0);
		}
#ifdef PTREE_MPATH
		struct rtentry *headrt, *rt;
		headrt = tt->data;
#ifdef DEBUG
		if(head->pnh_offset == 4){
			printf("-ptree_deladdr: gate[%p] ",gate);
			sprint_inet_ntoa(AF_INET, gate);
			printf("/%d\n",len);
		} else {
			printf("-ptree_deladdr: gate[%p] ",gate);
			sprint_inet_ntoa(AF_INET6, gate);
			printf("/%d\n",len);
		}
#endif
		if(headrt->mpath_array){
			rt = rt_mpath_matchgate(headrt,gate);
			if( ! rt_mpath_delete(headrt,rt) )
				return (0);
			return (tt);
		}
#endif
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
		dprint(("-ptree_inithead Start: pnh[%p]\n",head));

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
		dprint(("-ptree_init Start\n"));
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
	//if (ptree_inithead((void **)(void *)&rn_maskhead, 0) == 0)
	//	panic("ptree_init 2");

}

/*
 *  functions for multi path routing.
 */
#ifdef PTREE_MPATH
		int
ptree_mpath_capable(struct ptree_node_head *pnh)
{
		return pnh->pnh_multipath;
}

		uint32_t
ptree_mpath_count(struct rtentry *rt)
{
		dprint(("-ptree_mpath_count Start\n"));
		struct rtentry **rt1;
		uint32_t i = 0;

		rt1 = rt->mpath_array;
		/* count mpath_array */
		while (rt1 != NULL) {
				rt1++;
				i++;
		}
		dprint(("-ptree_mpath_count End: count = %d\n",i));
		return (i);
}

		struct rtentry *
rt_mpath_matchgate(struct rtentry *rt, struct sockaddr *gate)
{
		uint32_t	i = 0;
		//struct ptree_node *rn, **match;
		struct rtentry **match;
		dprint(("-rt_mpath_matchgate Start: rt[%p]\n",rt));

		//rn = (struct ptree_node *)rt;
		if (!rt->mpath_array){
				dprint(("-rt_mpath_matchgate: not have multipath\n"));
				return rt;
		}
		else
				match = rt->mpath_array;

		if (!gate)
				return NULL;

		/* beyond here, we use rn as the master copy */
		do {
				rt = *match;
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

		return *match;
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
		struct rtentry *rt0,**rt1;
		dprint(("-rt_mpath_delete Start\n"));

		if (!headrt || !rt)
				return (0);
		
		rt0 = headrt;
		n = ptree_mpath_count(rt0);
		rt1 = rt0->mpath_array;
		
		while (*rt1) {
				if (*rt1 == rt) {
						rt0->mpath_array[i] = rt0->mpath_array[n-1];
						rt0->mpath_array[n-1] = NULL;
						return (1);
				}
				rt1++;
				i++;
		}
		return (0);
}

/*
 * check if we have the same key/mask/gateway on the table already.
 */
		int
rt_mpath_conflict(struct ptree_node_head *pnh, struct rtentry *rt,
				struct sockaddr *dst /**netmask*/)
{
		struct ptree_node *rn;
		struct rtentry *rt0, **rt1;
		//struct sockaddr *sa0, *sa;
		//char *p, *q, *eq;
		//int same, l, skip;
		int l;
		dprint(("-rt_mpath_conflict Start\n"));
		l = (int)LEN(dst);

		rn = pnh->rnh_lookup((char *)dst, l, pnh->pnh_treetop);
		if (!rn)
				return 0;

		/*
		 * unlike other functions we have in this file, we have to check
		 * all key/mask/gateway as rnh_lookup can match less specific entry.
		 */
		rt0 = rn->data;
		//sa0 = *rt_key(rt0); sa = *rt_key(rt);

		/* compare key. */
#if 0
		if (sa0->sa_len != sa->sa_len ||
						bcmp(rt_key(rt0), rt_key(rt), sa0->sa_len))
				goto different;
#endif
		if (rt_key(rt0)->sa_len != rt_key(rt)->sa_len ||
						bcmp(rt_key(rt0), rt_key(rt), rt_key(rt0)->sa_len))
				goto different;
		rt1 = rt0->mpath_array;
		/* key/mask were the same.  compare gateway for all multipaths */
		do {
				if ((*rt1)->rt_gateway->sa_family == AF_LINK) {
						if ((*rt1)->rt_ifa->ifa_addr->sa_len != rt->rt_ifa->ifa_addr->sa_len ||
										bcmp((*rt1)->rt_ifa->ifa_addr, rt->rt_ifa->ifa_addr, 
												(*rt1)->rt_ifa->ifa_addr->sa_len))
								continue;
				} else {
						if ((*rt1)->rt_gateway->sa_len != rt->rt_gateway->sa_len ||
										bcmp((*rt1)->rt_gateway, rt->rt_gateway,
												(*rt1)->rt_gateway->sa_len))
								continue;
				}

				/* all key/mask/gateway are the same.  conflicting entry. */
				return EEXIST;
		} while ((rt1++) != NULL);

different:
		dprint(("-rt_mpath_conflict: different\n"));
		return 0;
}

		void
rtalloc_mpath_fib(struct route *ro, uint32_t hash, u_int fibnum)
{
		u_int32_t n;
		struct rtentry *rt, *rt0;
		//struct ptree_node *rn;
		dprint(("-rtallc_mpath_fib Start\n"));

		/*
		 * XXX we don't attempt to lookup cached route again; what should
		 * be done for sendto(3) case?
		 */
		if (ro->ro_rt && ro->ro_rt->rt_ifp && (ro->ro_rt->rt_flags & RTF_UP))
				return;				 
		ro->ro_rt = rtalloc1_fib(&ro->ro_dst, 1, 0, fibnum);
		//rn = (struct ptree_node *)ro->ro_rt;
		/* if the route does not exist or it is not multipath, don't care */
		if (ro->ro_rt == NULL)
				return;
		rt0 = ro->ro_rt;
		if (rt0->mpath_array == NULL) {
				RT_UNLOCK(ro->ro_rt);
				return;
		}

		/* beyond here, we use rn as the master copy */
		n = ptree_mpath_count(rt0);

		/* gw selection by Modulo-N Hash (RFC2991) XXX need improvement? */
		hash += hashjitter;
		hash %= n;
		rt = rt0->mpath_array[n];
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
		struct ptree_node_head *rnh;
		dprint(("-ptree4_mpath_inithead Start\n"));

		hashjitter = arc4random();
		if (in_inithead(head, off) == 1) {
				rnh = (struct ptree_node_head *)*head;
				rnh->pnh_multipath = 1;
				return 1;
		} else
				return 0;
}
#endif

#ifdef INET6
		int
ptree6_mpath_inithead(void **head, int off)
{
		struct ptree_node_head *rnh;
		dprint(("-ptree6_mpath_inithead Start\n"));

		hashjitter = arc4random();
		if (in6_inithead(head, off) == 1) {
				rnh = (struct ptree_node_head *)*head;
				rnh->pnh_multipath = 1;
				return 1;
		} else
				return 0;
}
#endif
#endif /* PTREE_MPATH */
