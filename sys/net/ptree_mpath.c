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

/* include file for debug */
#include <sys/types.h>
#if 0
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#endif
#include <netinet/in.h>

#include <rpc/rpc.h>
#include <rpc/nettype.h>
#include <rpc/rpc_com.h>

//char tmp[255];  /* string for debug */

static int  max_keylen;
static char *pn_zeros, *pn_ones;
extern char mask[];
#ifdef PTREE_MPATH
static uint32_t max_multipath;
#endif


#define LEN(x) (*(const u_char *)(x))

static struct ptree_node *ptree_insert(void *v_arg, void *m_arg,
			   	struct ptree_node_head *head, int *dupentry);
static int ptree_walktree(struct ptree_node_head *h, walktree_f_t *f, void *w);

#ifdef DEBUG
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
		int max = rt0->mpath_counter;

		if(mrt){ /* muluti path */
			int i = 0;
			while(mrt[i] && i <= max){
				printf("%24s [%p] ","multipath",mrt[i]);
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
#endif /* DEBUG */

int
create_masklen(char *m, struct ptree_node_head *head)
{
	int bytes, bits, keylen;
	unsigned char bitmask = 0xff;
	unsigned char diff;
		
	/* count mask_len */
	keylen = bytes = head->pnh_offset;
	if(LEN(m) <= keylen) 
		return 8*keylen;
	
	while(m[bytes] & bitmask)
		bytes++;
	
 	diff = m[bytes-1] ^ bitmask;
	if(diff){
		/* support CIDR */
		bits = 8*(bytes-1);
		dprint(("create_masklen: len_bytes[%d]\n",bytes-1));
 		bitmask = 0x80;
 		while (/*bits < salen && */! (bitmask & diff)) {
    	  bits++;
    	  bitmask >>= 1;
   		}
			keylen = bits;
		} else
			keylen = 8*bytes;

		return keylen;
}
	static struct ptree_node 
*ptree_insert(v_arg, m_arg, head, dupentry)  
	void *v_arg, *m_arg;
	struct ptree_node_head *head;
	int *dupentry;
{
	char *v = v_arg, *m = m_arg;
	register char *cp;
	struct ptree_node *top = head->pnh_top, *t, *tt;
	int len, salen, bits, bytes;
	
	if(head->pnh_offset == INET_HEADOFF )
		salen = len = (int)8*LEN(v) - SIN_ZERO;
	else
		salen = len = (int)8*LEN(v) - SIN6_ZERO;
	dprint(("ptree_insert: salen [%d]bytes\n",salen/8));
#if DEBUG
	struct sockaddr *sa = (struct sockaddr *)v, *sa_m = (struct sockaddr *)m;
	printf("ptree_insert: addr[");
	sprint_inet_ntoa(sa->sa_family, sa);
	printf("/%d(bytes)] ",sa->sa_len);
	if(m){
		printf("mask[");
		sprint_inet_ntoa(sa_m->sa_family, sa_m);
		printf("/%d(bytes)]",sa_m->sa_len);
	}
	printf("\n");
#endif
	
	if(m /*&& (LEN(m) > head->pnh_offset)*/){
		dprint(("ptree_insert: LEN(m)=[%d]bytes\n",LEN(m)));
		len = create_masklen(m,head);
		dprint(("ptree_insert: masklen_bits[%d]\n",len - 8*head->pnh_offset));
	}
	//else if( (m && (LEN(m) <= head->pnh_offset)) )
	//	len = 8*head->pnh_offset;

	if (!top)
		goto on1;
	
	if ( (t = ptree_search(v, len, head->pnh_treetop)) == NULL )
		goto on1;
	
	/* check key duplication */
	char *cplim = v;
	cp = t->key;
	bytes = len / 8;
	
	if ( !memcmp(cp,cplim,bytes) ){
		/* support CIDER */
		if ( (bits = len % 8) != 0 ){
			if( ((cp[bytes] ^ cplim[bytes]) & mask[bits]) && t->keylen != len)
				goto on1;
		}
		*dupentry = 1;
		return t;
	}
	
on1:
	*dupentry = 0;
	void *data = NULL;

	dprint(("ptree_insert: len_bits[%d]\n",len - 8*head->pnh_offset));
	tt = ptree_add(v, len, data, head->pnh_treetop);
	/* set netmask */
	if(len%8)
		bytes = len/8 + 1;
	bytes = len/8;
	
	cp = tt->key + bytes;
	memset(cp,0,(salen-len)/8);
	return (tt);
}

	int
ptree_refines(m_arg, n_arg)
	void *m_arg, *n_arg;
{
	register char *m = m_arg, *n = n_arg;
	register char *lim, *lim2 = lim = n + LEN(n);
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
	struct sockaddr *v = v_arg;
	register struct ptree_node *t = head->pnh_top;
	
	if(!t){
		dprint(("tree is empty\n"));
		return 0;
	}

	register char *cp;
	char *cplim;
	struct ptree_node *saved_t;
	int bytes, bits;
	
	//if((bytes = LEN(v)) < head->pnh_offset)
	bytes = sizeof(struct sockaddr);
	bits = 8 * bytes;
#if DEBUG
	dprint(("ptree_matchaddr: v["));
	sprint_inet_ntoa(sa->sa_family, sa);
	dprint(("/%d(bytes)] ",LEN(v)));
#endif
	/* if ipv6, sin6_port must be zero */
	if(v->sa_family == AF_INET6){
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)v;
		sin6->sin6_port = 0;
	}
		
	t = saved_t = ptree_search((char *)v, bits, head->pnh_treetop);
	if( !saved_t ){
		dprint(("not match(no entry)\n"));
		return 0;
	}

	cp = t->key; cplim = (char *)v;
	bytes = t->keylen / 8;
	if ( memcmp(cp,cplim,bytes) != 0 ){
		dprint(("not match(key diff)\n"));
		return 0;
	}
	/* support CIDER */
	bits = t->keylen % 8;
	if ( bits != 0 ){
		dprint(("CIDER_len[%d bits], ",bits));
		if( ((cp[bytes] ^ cplim[bytes]) & mask[bits]) ){
			dprint(("not match(netmask diff)\n"));
			return 0;
		}
	}
	/*
	 * match exactly as a host.
	 */
#if DEBUG
	dprint(("match["));
	sa = (struct sockaddr *)t->key;
	sprint_inet_ntoa(sa->sa_family, sa);
	dprint(("]\n"));
#endif
	return t;
}


		struct ptree_node *
ptree_addroute(v_arg, n_arg, head, rt)
		void *v_arg, *n_arg;
		struct ptree_node_head *head;
		struct rtentry *rt;
{
		register struct ptree_node *tt;
		struct ptree_node *saved_tt;
		int keyduplicated;
	//	struct rtentry *rt;
		
	//	rt = (struct rtentry *)rt_node;
		/*
		 * Deal with duplicated keys: attach node to previous instance
		 */
		saved_tt = tt = ptree_insert(v_arg, n_arg, head, &keyduplicated);
		
#ifdef PTREE_MPATH /* multi path */
		if (keyduplicated) {
			int n;
			struct rtentry *rt0, **rt_array;
				
			rt0 = tt->data;
			n = ptree_mpath_count(rt0);
			
			if(!n){
				/* if it is first multipath */
				R_Malloc(rt_array, struct rtentry **,
											 	max_multipath*sizeof(struct rtentry *));
				memset(rt_array, 0, max_multipath*sizeof(struct rtentry *));
				rt_array[0] = rt0;
				rt_array[1] = rt;
				rt0->rt_flags |= RTF_MULTIPATH;
				rt0->mpath_array = rt_array;
			} else if(n+1 == max_multipath) {
				/* if number of path is over MAX_MULTIPATH */
				struct rtentry **tmp;
				tmp = rt0->mpath_array;
				
				R_Realloc(tmp, struct rtentry **, 
												5*max_multipath*sizeof(struct rtentry *));
				if(tmp == NULL)
					return NULL;
				else
					rt_array = tmp;
				
				max_multipath *= 5;
				rt_array[n+1] = rt;
				rt0->mpath_array = rt_array;
			} else {
				rt_array = rt0->mpath_array;
				rt_array[n+1] = rt;
			}

			rt0->mpath_counter = n + 1;
			rt->rt_flags |= RTF_MULTIPATH;
			rt->rt_nodes = tt;
			return tt;
		}
#else
		if (keyduplicated) 
			return NULL;
#endif /* mluti path */
		tt->data = rt;
		rt->rt_nodes = tt;
		rt->mpath_counter = 0;
		return tt;
}


		struct ptree_node *
ptree_deladdr(v_arg, gate_arg, head)
		void *v_arg, *gate_arg;
		struct ptree_node_head *head;
{
		dprint(("ptree_deladdr Start\n"));
		register struct ptree_node *tt;
		struct ptree_node *saved_tt, *top;
		char *v;
		struct sockaddr *gate;
		unsigned int bits, bytes;

		v = v_arg;
		gate = gate_arg;
		top = head->pnh_top;
		bits = (int)8*LEN(v);

		tt = saved_tt = ptree_search(v, bits, head->pnh_treetop);

		if (!saved_tt){
				dprint(("ptree_deladdr: no entry in the tree\n"));
				return (0);
		}
		
		register char *cp, *cplim;
		cp = tt->key; cplim = v; bytes = tt->keylen / 8;
		if ( memcmp(cp, v, bytes) != 0 )
				return (0);
		/* support CIDER */
		if ( (bits = tt->keylen % 8) != 0 ){
			dprint(("v_bits[%d] ",bits));
			if( ((cp[bytes] ^ cplim[bytes]) & mask[bits]) ){
				dprint(("ptree_deladdr: not match\n"));
				return 0;
			}
		}
		
		struct rtentry *headrt, *rt;
		rt = headrt = tt->data;
#ifdef PTREE_MPATH
		if(headrt->mpath_array){
			dprint(("ptree_delete: rtentrry has mpath_array\n"));
			if ( (rt = rt_mpath_matchgate(headrt,gate)) != NULL ){
				struct ptree_node *tmprn;
			
  				XRTMALLOC(tmprn, struct ptree_node *, sizeof(struct ptree_node));
				memcpy(tmprn,tt,sizeof(struct ptree_node));
				tmprn->data = rt;
				if( ! rt_mpath_delete(headrt,rt) )
					return (tmprn);
				XRTFREE(tmprn);
			}
			else
				return (0);
		}
#endif
		/* compare gateway */
		if( gate && memcmp(gate, rt->rt_gateway, LEN(gate)) != 0 )
			return 0;
		dprint(("ptree_deladdr: call ptree_remove\n"));
		ptree_remove(tt);
		return (tt);
}


		static int
ptree_walktree(h, f, w)
		struct ptree_node_head *h;
		walktree_f_t *f;
		void *w;
{
	/*
	 * This gets complicated because we may delete the node
	 * while applying the function f to it, so we need to calculate
	 * the successor node in advance.
	 */
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

#if 0
		printf("-ptree_init: CPU %e MHz\n",cpu_frequency);
#endif
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

		unsigned int
ptree_mpath_count(struct rtentry *rt)
{
		return rt->mpath_counter;
}

		struct rtentry *
rt_mpath_matchgate(struct rtentry *rt, struct sockaddr *gate)
{
		uint32_t	i = 0, n;
		struct rtentry **match;
		dprint(("rt_mpath_matchgate Start\n"));

		if (!rt->mpath_array){
				dprint(("rt_mpath_matchgate End: mpath_array is NULL\n"));
				return rt;
		}
		else
				match = rt->mpath_array;

		if (!gate){
				dprint(("rt_mpath_matchgate End: gateway is NULL\n"));
				return NULL;
		}
		n = ptree_mpath_count(rt);
		/* beyond here, we use rn as the master copy */
		do {
				rt = match[i];
				dprint(("rt_matchgate: check rt[%d]=%p\n",i,rt));
				/*
				 * we are removing an address alias that has 
				 * the same prefix as another address
				 * we need to compare the interface address because
				 * rt_gateway is a special sockadd_dl structure
				 */
				if (rt->rt_gateway->sa_family == AF_LINK) {
						if (!memcmp(rt->rt_ifa->ifa_addr, gate, gate->sa_len)){
								dprint(("rt_mpath_matchgate: match rt[%d](AF_LINK)\n",i));
								return rt;
						}
				} else {
						if ( /*(rt->rt_gateway->sa_len == gate->sa_len) &&*/
										!memcmp(rt->rt_gateway, gate, gate->sa_len)){
								dprint(("rt_mpath_matchgate: match rt[%d]=%p\n",i,rt));
								return rt;
						}
				}
				i++;
		} while ( i <= n );

		dprint(("rt_matchgate End: not match\n"));
		return NULL;
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
		//struct sockaddr *sa0, *sa1;
		struct ptree_node *rn = headrt->rt_nodes;
		dprint(("rt_mpath_delete Start\n"));

		if (!headrt || !rt)
				return (0);
		
		rt0 = headrt;
		//sa0 = rt->rt_gateway;
		n = ptree_mpath_count(rt0);
		rt1 = rt0->mpath_array;
		dprint(("rt_mpath_delete: mpath_count[%d]\n",n));
		
		while (rt1[i] && i <= n) {
			//sa1 = rt1[i]->rt_gateway;
			//if (memcmp(sa0,sa1,sa1->sa_len/8) == 0) {
			if (rt1[i] == rt) {
				if(n == 0){ /* case: single path */
					rt1 = NULL;
					rt0->rt_flags &= ~RTF_MULTIPATH;
					return (1);
				}
				if(rt0 == rt1[i] && i == 0){ /* case: delete entry is array's top */
					dprint(("debug: case array's top\n"));
					/* move mpath_array pointer */
					rn->data = rt1[n];
					rt1[n]->mpath_array = rt1;
					/* swap match entry and tail's entry */
					rt1[i] = rt1[n];
					rt1[n] = NULL;
					rt0 = rt1[0];
				}
				else if(n == i) { /* case: delete entry is array's tail */
					dprint(("debug: case array's tail\n"));
					rt1[i] = NULL;
				}
				else {
					/* swap match entry and tail's entry */
					rt1[i] = rt1[n];
					rt1[n] = NULL;
				}
				
				rt0->mpath_counter = n - 1;
				return (0);
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
								struct sockaddr *dst, struct sockaddr *netmask)
{
		dprint(("rt_mpath_conflict: Start\n"));
		struct ptree_node *rn;
		struct rtentry *rt0, **rt1;
		int bits = 8*LEN(dst), bytes = LEN(dst);
		char *cp,*cplim;
		
		if(netmask && (LEN(netmask) > pnh->pnh_offset)){
			unsigned char bitmask = 0xff;
			unsigned char diff;
			
			bytes = pnh->pnh_offset;
			cp = (char *)netmask;
			while(cp[bytes] & bitmask)
				bytes++;
		
		 	diff = cp[bytes-1] ^ bitmask;
			if(diff){
				/* support CIDR */
				bits = 8*(bytes - 1);
		 		bitmask = 0x80;
		 		while (bits < 8*LEN(dst) && ! (bitmask & diff)) {
	    	  bits++;
	    	  bitmask >>= 1;
	   		}
			}
		 	else
				bits = 8*bytes;
		}
		
		dprint(("rt_mpath_conflict: bits[%d] bytes[%d]\n",bits, bytes));
		
		rn = ptree_search((char *)dst, bits, pnh->pnh_treetop);
		if (!rn){
				dprint(("rt_mpath_conflict: this dst-key has no-entry\n"));
				return 0;
		}

#if 0
	struct sockaddr *sa = (struct sockaddr *)rn->key;
	printf("rt_mpath_conflict: rn->key[");
	sprint_inet_ntoa(sa->sa_family, sa);
	printf("/%d]\n",rn->keylen);
#endif
		cp = rn->key; cplim = (char *)dst;
		/* compare key. */
		if ( memcmp(cp,cplim,rn->keylen/8) != 0 || bits != rn->keylen )
			goto different;
		/* support CIDER */
		if( (bits = rn->keylen % 8) != 0 ){
			dprint(("rt_mpath_conflict: support CIDER\n"));
			if( (cp[bytes]^cplim[bytes]) & mask[bits] )
				goto different;
		}
		/*
		 * unlike other functions we have in this file, we have to check
		 * all key/mask/gateway as rnh_lookup can match less specific entry.
		 */
		rt0 = rn->data;
		
		rt1 = rt0->mpath_array;
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
				dprint(("rt_mpath_conflict: conflicting entry\n"));
				return EEXIST;
		}
		/* key/mask were the same.  compare gateway for all multipaths */
		int n = ptree_mpath_count(rt0);
		int i = 0;
		do {
				/* check all entry */
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
				dprint(("rt_mpath_conflict: conflicting entry\n"));
				return EEXIST;
		} while ((++i) <= n);

different:
		dprint(("rt_mpath_conflict: different\n"));
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
		rt = rt0->mpath_array[hash];
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

	struct rtentry *
multipath_nexthop (unsigned int seed, struct rtentry *nexthops)
{
	struct rtentry *rt, **rt_array;
	unsigned int hash;
	int n = ptree_mpath_count(nexthops);
	
	rt = nexthops;

	if((rt_array = rt->mpath_array) == NULL)
		return rt;
	
	hash = seed % (n+1);
	rt = rt_array[hash];
	dprint(("multipath_nexthop: base_rt[%p] flow[%u] rt_select[%d/%d]\n",nexthops,seed,hash,n));
#if DEBUG
	printf(" rt_num[%d] ",hash);
	struct sockaddr *sa = (struct sockaddr *)rt->rt_gateway;
	printf("gate[");
	sprint_inet_ntoa(sa->sa_family, sa);
	printf("]");
#endif
	return rt;
}

extern int	in6_inithead(void **head, int off);
extern int	in_inithead(void **head, int off);

#ifdef INET
		int
ptree4_mpath_inithead(void **head, int off)
{
		struct ptree_node_head *rnh;

		hashjitter = arc4random();
		max_multipath = 20;
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

		hashjitter = arc4random();
		max_multipath = 20;
		if (in6_inithead(head, off) == 1) {
				rnh = (struct ptree_node_head *)*head;
				rnh->pnh_multipath = 1;
				return 1;
		} else
				return 0;
}
#endif
#endif /* PTREE_MPATH */
