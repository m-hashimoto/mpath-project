/*
 * ptree-mpath header
 */
#ifndef _PTREE_MULTIPATH_H_
#define _PTREE_MULTIPATH_H_

#ifdef _KERNEL
#include <sys/_lock.h>
#include <sys/_mutex.h>
#include <sys/_rwlock.h>
#endif /* _KERNEL */

#define DEBUG 1

#ifdef PTREE_MPATH
#define MAX_MPATH 5
#endif /* PTREE_MPATH */

typedef int walktree_f_t(struct ptree_node *, void *);

struct ptree_node_head {
		struct ptree *pnh_treetop;
		int      pnh_addsize;           /* permit, but not require fixed keys */
		int      pnh_pktsize;           /* permit, but not require fixed keys */
#ifdef PTREE_MPATH
		int		pnh_multipath;
#endif /* PTREE_MPATH */
		struct  ptree_node *(*pnh_addaddr)
				(void *v, void *mask, struct ptree_node_head *head);
		struct  ptree_node *(*pnh_addpkt)       /* add based on packet hdr */
				(void *v, void *mask, struct ptree_node_head *head);
		struct  ptree_node *(*pnh_deladdr)      /* remove based on sockaddr */
				(void *v, void *mask, struct ptree_node_head *head);
		struct  ptree_node *(*pnh_delpkt)       /* remove based on packet hdr */
				(void *v, void *mask, struct ptree_node_head *head);
		struct  ptree_node *(*pnh_matchaddr)    /* locate based on sockaddr */
				(void *v, int vlen, struct ptree_node_head *head);
		struct  ptree_node *(*pnh_lookup)       /* locate based on sockaddr */
				(void *v, void *mask, int keylen, struct ptree_node_head *head);
		struct  ptree_node *(*pnh_matchpkt)     /* locate based on packet hdr */
				(void *v, struct ptree_node_head *head);
		int     (*pnh_walktree)                 /* traverse tree */
				(struct ptree_node_head *head, walktree_f_t *f, void *w);
		int     (*pnh_walktree_from)            /* traverse tree below a */
				(struct ptree_node_head *head, void *a, void *m,
				 walktree_f_t *f, void *w);
		void    (*pnh_close)         /* do something when the last ref drops */
				(struct ptree_node *rn, struct ptree_node_head *head);
#ifdef _KERNEL
		struct rwlock rnh_lock;
#endif /* _KERNEL */
}

#define pnh_top pnh_treetop->top

#ifndef _KERNEL
#define R_Malloc(p, t, n) (p = (t) malloc((unsigned int)(n)))
#define R_Zalloc(p, t, n) (p = (t) calloc(1,(unsigned int)(n)))
#define Free(p) free((char *)p);
#else /* ifdef _KERNEL */
#define R_Malloc(p, t, n) (p = (t) malloc((unsigned long)(n), M_RTABLE, M_NOWAIT))
#define R_Zalloc(p, t, n) (p = (t) malloc((unsigned long)(n), M_RTABLE, M_NOWAIT | M_ZERO))
#define Free(p) free((caddr_t)p, M_RTABLE);

#define	RADIX_NODE_HEAD_LOCK_INIT(rnh)	\
		rw_init_flags(&(rnh)->rnh_lock, "radix node head", 0)
#define	RADIX_NODE_HEAD_LOCK(rnh)	rw_wlock(&(rnh)->rnh_lock)
#define	RADIX_NODE_HEAD_UNLOCK(rnh)	rw_wunlock(&(rnh)->rnh_lock)
#define	RADIX_NODE_HEAD_RLOCK(rnh)	rw_rlock(&(rnh)->rnh_lock)
#define	RADIX_NODE_HEAD_RUNLOCK(rnh)	rw_runlock(&(rnh)->rnh_lock)
#define	RADIX_NODE_HEAD_LOCK_TRY_UPGRADE(rnh)	rw_try_upgrade(&(rnh)->rnh_lock)


#define	RADIX_NODE_HEAD_DESTROY(rnh)	rw_destroy(&(rnh)->rnh_lock)
#define	RADIX_NODE_HEAD_LOCK_ASSERT(rnh) rw_assert(&(rnh)->rnh_lock, RA_LOCKED)
#define	RADIX_NODE_HEAD_WLOCK_ASSERT(rnh) rw_assert(&(rnh)->rnh_lock, RA_WLOCKED)
#endif /* _KERNEL */

void     ptree_init(void);
int      ptree_inithead(void **, int),
		 ptree_refines(void *, void *);
struct ptree_node *ptree_addroute (void *, void *, struct ptree_node_head *),
				  *ptree_deladdr(void *, void *, struct ptree_node_head *),
				  *ptree_matchaddr(void *, struct ptree_node_head *);

/*
 * Patricia trie API with multipath support
 */

#ifdef PTREE_MPATH
struct route;
struct rtentry;
struct sockaddr;
int     ptree_mpath_capable(struct ptree *);
u_int32_t ptree_mpath_count(struct ptree_node *);
struct rtentry *rt_mpath_matchgate(struct rtentry *, struct sockaddr *);
int rt_mpath_conflict(struct ptree *, struct rtentry *,
				struct sockaddr *);
void rtalloc_mpath_fib(struct route *, u_int32_t, u_int);
#define rtalloc_mpath(_route, _hash) rtalloc_mpath_fib((_route), (_hash), 0)
struct ptree_node *ptree_mpath_lookup(void *, void *, struct ptree *);
int rt_mpath_delete(struct rtentry *, struct rtentry *);
int     ptree4_mpath_inithead(void **, int);
int     ptree6_mpath_inithead(void **, int);
#endif /* PTREE_MPATH */
#undef DEBUG

#endif /*_PTREE_MPATH_H_*/
