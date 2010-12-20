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
	if(af == AF_INET){
		char str[INET_ADDRSTRLEN];
		struct in_addr addr = ((struct sockaddr_in *)(sa))->sin_addr;
		__rpc_inet_ntop(AF_INET, &addr, str, INET_ADDRSTRLEN);
		printf("%s",str);
	} else if(af == AF_INET6) {
		char str6[INET6_ADDRSTRLEN];
		struct in6_addr addr6 = ((struct sockaddr_in6 *)(sa))->sin6_addr;
		__rpc_inet_ntop(AF_INET6, &addr6, str6, INET6_ADDRSTRLEN);
		printf("%s",str6);
	}
}

#define INET_HEADOFF 4
#define INET6_HEADOFF 8

	int
debug_node_print(struct ptree_node *pn, int offset)
{
	if(!pn->key || !pn->keylen)
		return 1;
	
	printf("[%p] <0x%8p, 0x%8p> ",pn,pn->child[0],pn->child[1]);
	if(offset == 8){ /* IPv6 */
		sprint_inet_ntoa(AF_INET6,pn->key);
		printf("/%d\n",pn->keylen-8*offset);
	} else { /* IPv4 */
		sprint_inet_ntoa(AF_INET,pn->key);
		printf("/%d\n",pn->keylen-8*offset);
	}

#ifdef PTREE_MPATH
	if(pn->data){
		struct rtentry *rt, *rt0 = pn->data;
		struct rtentry **mrt = rt0->mpath_array;

		if(mrt){ /* muluti path */
			int i = 0;
			while(mrt[i]){
				printf("%24s [%p] ","malutipath",mrt[i]);
				rt = mrt[i];
				if(offset == INET6_HEADOFF){
					sprint_inet_ntoa(AF_INET6,rt->rt_gateway);
					printf(" flags[0x%x]\n",rt->rt_flags);
				} else {
					sprint_inet_ntoa(AF_INET,rt->rt_gateway);
					printf(" flags[0x%x]\n",rt->rt_flags);
				}
				i++;
			}
		}
		else{ /* single path */
			if (rt0->rt_gateway->sa_family == AF_LINK) {
				printf("%24s [%p] ","link",pn->data);
				if(offset == INET6_HEADOFF){
					sprint_inet_ntoa(AF_INET6,rt0->rt_ifa->ifa_addr);
					printf(" flags[0x%x]\n",rt0->rt_flags);
				} else {
					sprint_inet_ntoa(AF_INET,rt0->rt_ifa->ifa_addr);
					printf(" flags[0x%x]\n",rt0->rt_flags);
				}
			} else {
				printf("%24s [%p] ","gateway",pn->data);
				if(offset == INET6_HEADOFF){
					sprint_inet_ntoa(AF_INET6,rt0->rt_gateway);
					printf(" flags[0x%x]\n",rt0->rt_flags);
				} else {
					sprint_inet_ntoa(AF_INET,rt0->rt_gateway);
					printf(" flags[0x%x]\n",rt0->rt_flags);
				}
			}
		}
#if 0
		unsigned char *str;
		int i;
		str = (unsigned char *)rt0->rt_gateway;
		printf("gateway: ");
		for(i=0;i < 16;i++)
			printf("%d.",str[i]);
		printf("/16\n");
#endif
	}
#endif /* PTREE_MPATH */
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
			debug_node_print(pn, pnh->pnh_offset);
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

#define SIN_ZERO 64
#define SIN6_ZERO 32

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
	int len;
	
	if(head->pnh_offset == INET_HEADOFF )
		len = (int)8*LEN(v) - SIN_ZERO;
	else
		len = (int)8*LEN(v) - SIN6_ZERO;
	
#ifdef DEBUG
	if(head->pnh_offset == INET_HEADOFF){
		printf("-ptree_insert: addr ");
		sprint_inet_ntoa(AF_INET, v);
		printf("/%d\n",len);
	} else {
		printf("-ptree_insert: addr ");
		sprint_inet_ntoa(AF_INET6, v);
		printf("/%d\n",len);
	}
#endif
	if(m)
		dprint(("-ptree_insert: LEN(m)=%d\n",LEN(m)));
	if(m && (LEN(m) > head->pnh_offset)){
		dprint(("-ptree_insert: LEN(m)=%d\n",LEN(m)));
		unsigned char bitmask = 0xff;
		len = head->pnh_offset;
		while(m[len] & bitmask)
			len++;
		len = 8*len;
#ifdef DEBUG
		if(head->pnh_offset == INET_HEADOFF){
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
		//dprint(("-ptree_insert: top is NULL\n"));
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
		if ( !memcmp(cp2,cplim,len/8) ){
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
	//dprint(("-ptree_insert End: insert tt[%p]\n",tt));
	return (tt);
}

#undef SIN_ZERO
#undef SIN6_ZERO

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
		struct rtentry *rt;
		
		rt = (struct rtentry *)rt_node;
		/*
		 * Deal with duplicated keys: attach node to previous instance
		 */
		saved_tt = tt = ptree_insert(v_arg, n_arg, head, &keyduplicated);
		
		/* default gateway "0.0.0.0/0" */
		char zero[LEN(v_arg)/8], *tmp;
		char *v = v_arg;

		memset(zero,0,sizeof(zero));
		tmp = v + head->pnh_offset;
		if(memcmp(tmp,zero,sizeof(tmp)) == 0){
			tt->keylen = 8*head->pnh_offset;
			dprint(("-ptree_insert: default gateway len[%d]\n",tt->keylen));
		}
		
		dprint(("-ptree_addroute: keyduplicated[%d]\n",keyduplicated));
#ifdef PTREE_MPATH /* multi path */
		if (keyduplicated) {
			int n;
			struct rtentry *rt0, **rt_array;
			dprint(("-ptree_addroute: if keyduplicated.\n"));
				
			rt0 = tt->data;
			dprint(("-ptree_addroute: rt0[%p] rt[%p]\n",rt0,rt));
				dprint(("-ptree_addroute: mpath_array[%p]\n",rt0->mpath_array));
			n = ptree_mpath_count(rt0);
			dprint(("-ptree_addroute: mpat_count[%d]\n",n));
			if(!n){
				dprint(("-ptree_addroute: add new mpath_array\n"));
				dprint(("-ptree_addroute: rt0 = %p rt = %p\n",rt0,rt));
				R_Malloc(rt_array, struct rtentry **, MAX_MULTIPATH*sizeof(struct rtentry *));
				memset(rt_array, 0, MAX_MULTIPATH*sizeof(struct rtentry *));
				rt_array[0] = rt0;
				rt_array[1] = rt;
				rt0->mpath_array = rt_array;
			} else {
				dprint(("-ptree_addroute: add new rt in array[%d]\n",n));
				rt_array = rt0->mpath_array;
				rt_array[n] = rt;
			}
			rt->rt_nodes = tt;
#if 0 /* Realloc */
			if(n == MAX_MULTIPATH){
				struct rtentry **tmp;
				
				R_Realloc(tmp, struct rtentry **, 
												10*MAX_MULTIPATH*sizeof(struct rtentry *));
				if(tmp==NULL){
					printf("realloc fault\n");
					return NULL;
				}
				else{
					rt_array = tmp;
					dprint(("-ptree_addroute: Realloc mpath_array[%p]\n",rt_array));
				}
			}
#endif
			rt->mpath_array = rt_array;
			return tt;
		}
#endif /* mluti path */
		tt->data = rt;
		rt->rt_nodes = tt;
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
			dprint(("-ptree_deladdr: rt[%p]\n",rt));
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
#if 0
	struct ptree_node *base, *next;
	register struct ptree_node *pn = h->pnh_top;
	/*
	 * This gets complicated because we may delete the node
	 * while applying the function f to it, so we need to calculate
	 * the successor node in advance.
	 */

	if(!pn)
		return (0);
	/* First time through node, go left */
	while (pn && pn->child[0])
		pn = pn->child[0];
	for (;;) {
		base = pn;
		if(!pn->parent)
			return (0);
		/* If at right child go back up, otherwise, go right */
		pn = pn->parent;
		while (pn && pn->parent && pn->child[1] == pn)
			pn = pn->parent;
		/* Find the next *leaf* since next node might vanish, too */
		for (pn = pn->parent->child[1]; !pn;)
			pn = pn->child[0];
		next = pn;
	}
#endif
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
		dprint(("-ptree_mpath_count: rt1[%p]\n",rt1));
		/* count mpath_array */
		while (rt1 && rt1[i]) {
				dprint(("-ptree_mpath_count: rt1[%d] = %p\n",i,rt1[i]));
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
				rt = match[i];
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
		} while ( match[i] );

		dprint(("-rt_mpath_matchgate End: rt[%p]\n",rt));
		return rt;
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
		struct sockaddr *sa0, *sa1;
		dprint(("-rt_mpath_delete Start\n"));

		if (!headrt || !rt)
				return (0);
		
		rt0 = headrt;
		sa0 = headrt->rt_gateway;
		n = ptree_mpath_count(rt0);
		rt1 = rt0->mpath_array;
		
		int l = 0;
		unsigned char *str = (unsigned char *)sa0;
		dprint(("headrt->rt_gateway[%p] ",sa0));
		for(l=0;l<16;l++)
			dprint(("%d.",str[l]));
		dprint(("/16\n"));
		
		while (rt1[i] && i < n) {
				dprint(("-rt_mpath_delete: rt1[%d]=[%p] rt[%p]\n",i,rt1[i],rt));
				sa1 = rt1[i]->rt_gateway;
				
				str = (unsigned char *)sa1;
				dprint(("rt1[%d]->rt_gateway[%p] ",i,sa1));
				for(l=0;l<16;l++)
					dprint(("%d.",str[l]));
				dprint(("/16\n"));
				
				dprint(("-rt_mpath_delete: memcmp[%d]\n",memcmp(sa0,sa1,sa0->sa_len) ));
				if (memcmp(sa0,sa1,sa0->sa_len) == 0) {
						dprint(("-rt_mpath_delete: match gate\n"));
						l=0;
						while (rt1[l] && l < n){
							dprint(("-rt_mpath_delete: rt1[%d]=[%p]\n",l,rt1[l]));
							l++;
						}
						
						rt1[i] = rt1[n-1];
						rt1[n-1] = NULL;

						l=0;
						while (rt1[l] && l < n-1){
							dprint(("-rt_mpath_delete: rt1[%d]=[%p]\n",l,rt1[l]));
							l++;
						}
						
						if(n == 1)
							Free(rt1);
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
rt_mpath_conflict(struct ptree_node_head *pnh, struct rtentry *rt,
								struct sockaddr *dst)
{
		struct ptree_node *rn;
		struct rtentry *rt0, **rt1;
		int len = 8*LEN(dst), i, n;
		char *cp,*cplim;
		
		dprint(("-rt_mpath_conflict Start\n"));
#ifdef DEBUG
		if(pnh->pnh_offset == 4){
			printf("-rt_mpath_conflict: dst ");
			sprint_inet_ntoa(AF_INET, dst);
			printf("/%d\n",len);
		}else{
			printf("-rt_mpath_conflict: dst ");
			sprint_inet_ntoa(AF_INET6, dst);
			printf("/%d\n",len);
		}
#endif

		//rn = pnh->rnh_lookup((char *)dst, len, pnh->pnh_treetop);
		rn = ptree_search((char *)dst, len, pnh->pnh_treetop);
		dprint(("-rt_mpath_conflict: rn[%p]\n",rn));
		if (!rn)
				return 0;

		cp = rn->key; cplim = (char *)dst; len = rn->keylen;
#ifdef DEBUG
		if(pnh->pnh_offset == 4){
			printf("-rt_mpath_conflict: rn ");
			sprint_inet_ntoa(AF_INET, cp);
			printf("/%d\n",len);
		}else{
			printf("-rt_mpath_conflict: rn ");
			sprint_inet_ntoa(AF_INET6, cp);
			printf("/%d\n",len);
		}
#endif
		/* compare key. */
		if ( memcmp(cp,cplim,len/8) != 0 )
			goto different;
		dprint(("-rt_mpath_conflict: match exactly as a host\n"));

		/*
		 * unlike other functions we have in this file, we have to check
		 * all key/mask/gateway as rnh_lookup can match less specific entry.
		 */
		rt0 = rn->data;
		
		rt1 = rt0->mpath_array;
		dprint(("-rt_mpath_conflict: rt0[%p] rt1[%p]\n",rt0,rt1));
		if(!rt1){
				if (rt0->rt_gateway->sa_family == AF_LINK) {
						if (rt0->rt_ifa->ifa_addr->sa_len != rt->rt_ifa->ifa_addr->sa_len ||
										bcmp(rt0->rt_ifa->ifa_addr, rt->rt_ifa->ifa_addr, 
												rt0->rt_ifa->ifa_addr->sa_len))
								goto different;
				} else {
						if (rt0->rt_gateway->sa_len != rt->rt_gateway->sa_len ||
										bcmp(rt0->rt_gateway, rt->rt_gateway,
												rt0->rt_gateway->sa_len))
								goto different;
				}

				/* all key/mask/gateway are the same.  conflicting entry. */
				return EEXIST;
		}
		/* key/mask were the same.  compare gateway for all multipaths */
		n = ptree_mpath_count(rt0);
		i = 0;
		do {
				dprint(("-rt_mpath_conflict: rt1[%d]=[%p]\n",i,rt1[i]));
				if (rt1[i]->rt_gateway->sa_family == AF_LINK) {
						if (rt1[i]->rt_ifa->ifa_addr->sa_len != rt->rt_ifa->ifa_addr->sa_len ||
										bcmp(rt1[i]->rt_ifa->ifa_addr, rt->rt_ifa->ifa_addr, 
												rt1[i]->rt_ifa->ifa_addr->sa_len))
								continue;
				} else {
						if (rt1[i]->rt_gateway->sa_len != rt->rt_gateway->sa_len ||
										bcmp(rt1[i]->rt_gateway, rt->rt_gateway,
												rt1[i]->rt_gateway->sa_len))
								continue;
				}

				/* all key/mask/gateway are the same.  conflicting entry. */
				return EEXIST;
		} while ((++i) < n);

different:
		dprint(("-rt_mpath_conflict: different\n"));
		return 0;
}

		void
rtalloc_mpath_fib(struct route *ro, uint32_t hash, u_int fibnum)
{
		//u_int32_t n;
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
#if 0
		/* beyond here, we use rn as the master copy */
		n = ptree_mpath_count(rt0);

		/* gw selection by Modulo-N Hash (RFC2991) XXX need improvement? */
		hash += hashjitter;
		dprint(("-rtalloc_mpath_fib: hash[%u] hashjitter[%u]\n",hash,hashjitter));
		hash %= n;
		rt = rt0->mpath_array[hash];
		/* XXX try filling rt_gwroute and avoid unreachable gw  */
#endif
		rt = multipath_nexthop(hash,rt0);

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

	struct rtentry *
multipath_nexthop (unsigned int seed, struct rtentry *nexthops)
{
	struct rtentry *rt, **rt_array;
	unsigned int hash;
	int n;
	
	n = ptree_mpath_count(nexthops);
	rt_array = nexthops->mpath_array;
	hash = seed + hashjitter;
	
	dprint(("-multipath_nexthop: hash[%u] seed[%u]\n",hash,seed));
	hash %= n;
	rt = rt_array[hash];
	dprint(("-multipath_nexthop: rt[%p]\n",rt));
	return rt;
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
