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
#define INET_HEADOFF 4
#define INET6_HEADOFF 8
#define SIN_ZERO 64
#define SIN6_ZERO 32

static struct ptree_node *ptree_insert(void *v_arg, void *m_arg,
			   	struct ptree_node_head *head, int *dupentry);
static int ptree_walktree(struct ptree_node_head *h, walktree_f_t *f, void *w);

#ifdef DEBUG
#if 0
extern int open(const char *pathname, int flags);
extern ssize_t write(int fd, const void *buf, size_t count);
extern int close(int fd);
extern void	closelog(void);
extern void	openlog(const char *, int, int);
extern void	syslog(int, const char *, ...) __printflike(2, 3);

	void
dprint_ctof(int level,char *msg){ 
	//int fd;
	openlog("ptree_log",LOG_CONS | LOG_PID, LOG_KERN);

	if(DEBUG && level == P_DEBUG){
		syslog(LOG_DEBUG,msg);
#if 0
		fd = open("/var/log/ptree_debug.log",O_WRONLY | O_CREAT | O_APPEND);
		write(fd,msg,strlen(msg));
		close(fd);
#endif
	}else if(DEBUG && level == P_INFO){
		syslog(LOG_INFO,msg);
#if 0
		fd = open("/var/log/ptree_info.log",O_WRONLY | O_CREAT | O_APPEND);
		write(fd,msg,strlen(msg));
		close(fd);
#endif
	}
	closelog();
}
#endif

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

	static struct ptree_node 
*ptree_insert(v_arg, m_arg, head, dupentry)  
	void *v_arg, *m_arg;
	struct ptree_node_head *head;
	int *dupentry;
{
	char *v = v_arg, *m = m_arg;
	register char *cp;
	struct ptree_node *top = head->pnh_top, *t, *tt;
	int len, salen;
	
	if(head->pnh_offset == INET_HEADOFF )
		salen = len = (int)8*LEN(v) - SIN_ZERO;
	else
		salen = len = (int)8*LEN(v) - SIN6_ZERO;
	
#ifdef DEBUG
	struct sockaddr *sa = (struct sockaddr *)v, *sa_m = (struct sockaddr *)m;
	printf("ptree_insert: addr[");
	sprint_inet_ntoa(sa->sa_family, sa);
	printf("] ");
	if(m){
		printf("mask[");
		sprint_inet_ntoa(sa_m->sa_family, sa_m);
		printf("/%d]",sa_m->sa_len);
	}
	printf("\n");
#endif
	
	if(m && (LEN(m) > head->pnh_offset)){
		unsigned char bitmask = 0xff;
		unsigned char diff;
		len = head->pnh_offset;
		while(m[len] & bitmask)
			len++;
		
	 	diff = m[len-1] ^ bitmask;
		if(diff){
			/* support CIDR */
			dprint(("ptree_insert: diff[0x%x]\n",diff));
			len = 8*(len-1);
	 		bitmask = 0x80;
	 		while (len < salen && ! (bitmask & diff)) {
    	  len++;
    	  bitmask >>= 1;
   		}
		} else
			len = 8*len;
		dprint(("ptree_insert: masklen[%d]\n",len - 8*head->pnh_offset));
	}
	else if( (m && (LEN(m) <= head->pnh_offset)) )
		len = 8*head->pnh_offset;
	
	if (!top)
		goto on1;
	
	//long long int c0,c1,c2;
	//RDTSC(c0);
	//RDTSC(c1);
	t = ptree_search(v, len, head->pnh_treetop);
	//RDTSC(c2);
	//printf("-ptree_insert: RDTSC Start    :%lld clk\n",c0);
	//printf("-ptree_insert: RDTSC Interval :%lld clk\n",c1-c0);
	//printf("-ptree_insert: search Start   :%lld clk\n",c1);
	//printf("-ptree_insert: search End     :%lld clk\n",c2);
	//printf("-ptree_insert: ptree_search %lld[clk]\n",c2-c1-(c1-c0));
	if (!t)
		goto on1;

	//cp = v;
	{
		register char *cp2 = t->key;
		char *cplim = v;
		if ( !memcmp(cp2,cplim,len/8) ){
			*dupentry = 1;
			return t;
		}
	}
on1:
	*dupentry = 0;
	void *data = NULL;

	//RDTSC(c0);
	//RDTSC(c1);
	dprint(("ptree_insert: len[%d]\n",len - 8*head->pnh_offset));
	tt = ptree_add(v, len, data, head->pnh_treetop);
	//RDTSC(c2);
	//printf("-ptree_insert: RDTSC Start    :%lld clk\n",c0);
	//printf("-ptree_insert: RDTSC Interval :%lld clk\n",c1-c0);
	//printf("-ptree_insert: add Start      :%lld clk\n",c1);
	//printf("-ptree_insert: add End        :%lld clk\n",c2);
	//printf("-ptree_insert: ptree_add %lld[clk]\n",c2-c1-(c1-c0));
	/* set netmask */
	cp = tt->key + len/8;
	memset(cp,0,(salen-len)/8);
	return (tt);
}

#undef SIN_ZERO
#undef SIN6_ZERO

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
	char *v = v_arg;
	register struct ptree_node *t = head->pnh_top;
#ifdef DEBUG
	struct sockaddr *sa = (struct sockaddr *)v;
	dprint(("ptree_matchaddr: v["));
	if(sa->sa_family == AF_INET)
		sprint_inet_ntoa(AF_INET, sa);
	else
		sprint_inet_ntoa(AF_INET6, sa);
	dprint(("] "));
#endif
	
	if(!t){
		dprint(("tree is empty\n"));
		return 0;
	}

	register char *cp;
	char *cplim;
	struct ptree_node *saved_t;
	int v_bytes, v_bits;
	
	v_bits = (int)8*LEN(v);
	t = saved_t = ptree_search(v, v_bits, head->pnh_treetop);
	if( !saved_t ){
		dprint(("not match\n"));
		return 0;
	}

	cp = t->key; cplim = v; v_bytes = t->keylen / 8;
	if ( memcmp(cp,cplim,v_bytes) != 0 ){
		dprint(("not match\n"));
		return 0;
	}
	/* support CIDER */
	if ( (v_bits = t->keylen % 8) != 0 ){
		dprint(("v_bits[%d] ",v_bits));
		dprint(("cp[%x] cplim[%x] ",cp[v_bytes],cplim[v_bytes]));
		if( ((cp[v_bytes] ^ cplim[v_bytes]) & mask[v_bits]) ){
			dprint(("not match\n"));
			return 0;
		}
	}
	/*
	 * match exactly as a host.
	 */
	//sprintf(tmp,"ptree_matchaddr: match ptree_node[%p]\n",t);
	//dprint(P_DEBUG,tmp);
#ifdef DEBUG
	dprint(("match["));
	sa = (struct sockaddr *)t->key;
	if(sa->sa_family == AF_INET)
		sprint_inet_ntoa(AF_INET, sa);
	else
		sprint_inet_ntoa(AF_INET6, sa);
	dprint(("]\n"));
#endif
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
			rt->rt_nodes = tt;
			//sprintf(tmp,"ptree_addroute: rt0[%d]->%p\n",rt0->mpath_counter,rt);
			//dprint(P_DEBUG,tmp);
			return tt;
		}
#endif /* mluti path */
		tt->data = rt;
		rt->rt_nodes = tt;
		rt->mpath_counter = 0;
		//sprintf(tmp,"ptree_addroute: rt[%p]\n",rt);
		//dprint(P_DEBUG,tmp);
		return tt;
}


		struct ptree_node *
ptree_deladdr(v_arg, gate_arg, head)
		void *v_arg, *gate_arg;
		struct ptree_node_head *head;
{
		register struct ptree_node *tt;
		struct ptree_node *saved_tt, *top;
		char *v;
		struct sockaddr *gate;
		unsigned int len;

		v = v_arg;
		gate = gate_arg;
		top = head->pnh_top;
		len = (int)8*LEN(v);

		tt = saved_tt = ptree_search(v, len, head->pnh_treetop);

		if (!saved_tt)
				return (0);
		
		register char *cp, *cplim;
		cp = tt->key; cplim = v; len = tt->keylen;
		if ( memcmp(cp, v, len/8) != 0 )
				return (0);
		
#ifdef PTREE_MPATH
		struct rtentry *headrt, *rt;
		headrt = tt->data;
		
		if(headrt->mpath_array){
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
#if 0
		struct rtentry **rt1;
		uint32_t i = 0;

		rt1 = rt->mpath_array;
		/* count mpath_array */
		while (rt1 && rt1[i] && i < max_multipath)
				i++;
#endif
		return (rt->mpath_counter);
}

		struct rtentry *
rt_mpath_matchgate(struct rtentry *rt, struct sockaddr *gate)
{
		uint32_t	i = 0;
		struct rtentry **match;

		if (!rt->mpath_array)
				return rt;
		
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
						if (!memcmp(rt->rt_ifa->ifa_addr, gate, gate->sa_len/8))
								break;
				} else {
						if (rt->rt_gateway->sa_len == gate->sa_len &&
										!memcmp(rt->rt_gateway, gate, gate->sa_len/8))
								break;
				}
				i++;
		} while ( match[i] );

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
		//struct sockaddr *sa0, *sa1;
		struct ptree_node *rn = headrt->rt_nodes;

		if (!headrt || !rt)
				return (0);
		
		rt0 = headrt;
		//sa0 = rt->rt_gateway;
		n = ptree_mpath_count(rt0);
		rt1 = rt0->mpath_array;
		
		while (rt1[i] && i <= n) {
			//sa1 = rt1[i]->rt_gateway;
			//if (memcmp(sa0,sa1,sa1->sa_len/8) == 0) {
			if (rt1[i] == rt) {
				if(n == 0){ /* case: single path */
					rt1 = NULL;
					return (1);
				}
				if(rt0 == rt1[i] && i == 0){ /* case: delete entry is array's top */
					//printf("debug: case array's top\n");
					/* move mpath_array pointer */
					rn->data = rt1[n];
					rt1[n]->mpath_array = rt1;
					/* swap match entry and tail's entry */
					rt1[i] = rt1[n];
					rt1[n] = NULL;
					rt0 = rt1[0];
				}
				else if(n == i) { /* case: delete entry is array's tail */
					//printf("debug: case array's tail\n");
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
								struct sockaddr *dst)
{
		struct ptree_node *rn;
		struct rtentry *rt0, **rt1;
		int len = 8*LEN(dst), i, n;
		char *cp,*cplim;
		
		rn = ptree_search((char *)dst, len, pnh->pnh_treetop);
		if (!rn)
				return 0;

		cp = rn->key; cplim = (char *)dst; len = rn->keylen;
		/* compare key. */
		if ( memcmp(cp,cplim,len/8) != 0 )
			goto different;

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
				return EEXIST;
		}
		/* key/mask were the same.  compare gateway for all multipaths */
		n = ptree_mpath_count(rt0);
		i = 0;
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
				return EEXIST;
		} while ((++i) < n);

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
	int n;
	
	rt = nexthops;
	if((n = ptree_mpath_count(rt)) == 0)
		return rt;
	
	rt_array = rt->mpath_array;
	hash = seed + hashjitter;
	
	hash %= n+1;
	rt = rt_array[hash];
	//sprintf(tmp,"-multipath_nexthop: rt[%d]=%p\n",hash,rt);
	//dprint(P_DEBUG,tmp);
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
