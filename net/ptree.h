#ifndef _PTREE_H_
#define _PTREE_H_

#ifdef _KERNEL
#include <sys/_lock.h>
#include <sys/_mutex.h>
#include <sys/_rwlock.h>
#endif

//#if 0
#ifdef MALLOC_DECLARE
MALLOC_DECLARE(M_RTABLE);
#endif
//#endif /*0*/

#ifdef PTREE_MPATH
#define MAX_MPATH 5
#endif /* PTREE_MPATH */

struct ptree_node {
  struct  ptree_mask *rn_mklist;
  caddr_t key;
  caddr_t rn_mask;
  short   keylen;

  short	rn_bit;
  char	rn_bmask;
  u_char rn_flags;	/* enumerated next */
#define RNF_NORMAL	1
#define RNF_ROOT	2
#define RNF_ACTIVE	4
  struct ptree_node *parent;
  struct ptree_node *child[2];
  struct ptree_node *rn_dupedkey;
  void *data;
  int	lock;

#ifdef PTREE_MPATH
  int mpath_select;
  struct ptree_node mpath_array[MAX_MPATH];
#endif

  int rn_Off;
#ifdef RN_DEBUG
  int rn_info;
  struct ptree_node *rn_twin;
  struct ptree_node *rn_ybro;
#endif
};

#define rn_key key
#define rn_parent parent
#define rn_left child[0]
#define rn_right child[1]
#define rn_offset rn_Off

#if 0
#define PTREE_LEFT(x) (&(x)->child[0])
#define PTREE_RIGHT(x) (&(x)->child[1])
#endif /*0*/

struct ptree_mask {
	short   rm_bit;                 /* bit offset; -1-index(netmask) */ 
 	char    rm_unused;              /* cf. rn_bmask */
	u_char  rm_flags;               /* cf. rn_flags */
	struct  ptree_mask *rm_mklist;  /* more masks to try */
	union   {
		caddr_t rmu_mask;               /* the mask */
		struct  ptree_node *rmu_leaf;   /* for normal routes */
	}rm_rmu;
	int     rm_refs;                /* # of references to this struct */
};

#define rm_mask rm_rmu.rmu_mask
#define rm_leaf rm_rmu.rmu_leaf         /* extra field would make 32 bytes */
typedef int walktree_f_t(struct ptree_node *, void *);

struct ptree {
	struct ptree_node *top;
	int	 rnh_addsize;		/* permit, but not require fixed keys */
	int	 rnh_pktsize;  		/* permit, but not require fixed keys */
	struct ptree_node rnh_nodes[3];	/* empty tree for comon case */
	int	 rnh_multipath;		/* multipath capable ? */

	struct  ptree_node *(*rnh_addaddr)
		(void *v, void *mask,
		 struct ptree *head, struct ptree_node nodes[]);
	struct  ptree_node *(*rnh_addpkt) 	/* add based on packet hdr */
		(void *v, void *mask,
		 struct ptree *head, struct ptree_node nodes[]);
	struct  ptree_node *(*rnh_deladdr) 	/* remove based on sockaddr */
		(void *v, void *mask, struct ptree *head);  
  	struct  ptree_node *(*rnh_delpkt) 	/* remove based on packet hdr */
		(void *v, void *mask, struct ptree *head); 
 	struct  ptree_node *(*rnh_matchaddr) 	/* locate based on sockaddr */
		(void *v, struct ptree *head);
	struct  ptree_node *(*rnh_lookup) 	/* locate based on sockaddr */  
  		(void *v, void *mask, int keylen, struct ptree *head);
	struct  ptree_node *(*rnh_matchpkt)	/* locate based on packet hdr */
		(void *v, struct ptree *head);
	int     (*rnh_walktree)                 /* traverse tree */
		(struct ptree *head, walktree_f_t *f, void *w);
	int     (*rnh_walktree_from)            /* traverse tree below a */
		(struct ptree *head, void *a, void *m,
		 walktree_f_t *f, void *w);
	void    (*rnh_close)    	/* do something when the last ref drops */
		(struct ptree_node *rn, struct ptree *head);
#ifdef _KERNEL
	struct rwlock rnh_lock; 	/* locks entire */
#endif
};

#define rnh_treetop top

#ifdef _KERNEL
#define XRTMALLOC(p, t, n) (p = (t) malloc((unsigned long)(n), M_RTABLE, M_NOWAIT | M_ZERO))
#define XRTFREE(p) free((caddr_t)p, M_RTABLE)
#define XRTLOG(pri, fmt, ...) log (pri, fmt, __VA_ARGS__)
#define XRTASSERT(exp, string) KASSERT (exp, string)
#else /*_KERNEL*/
#define XRTMALLOC(p, t, n) (p = (t) malloc ((unsigned int)(n)))
#define XRTFREE(p) free((char *)p)
#define XRTLOG(pri, fmt, ...) printf (fmt, __VA_ARGS__)
#define XRTASSERT(exp, string) assert (exp)
#endif /*_KERNEL*/

#ifndef MIN
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#endif /*MIN*/


#ifndef _KERNEL
#define R_Malloc(p, t, n) (p = (t) malloc((unsigned int)(n)))
#define R_Zalloc(p, t, n) (p = (t) calloc(1,(unsigned int)(n)))
#define Free(p) free((char *)p);
#else
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

void ptree_node_lock (struct ptree_node *x);
void ptree_node_unlock (struct ptree_node *x);

struct ptree_node
	*ptree_lookup (void *key, void *mask, int keylen, struct ptree *t);
struct ptree_node *ptree_search (char *key, int keylen, struct ptree *t);
struct ptree_node 
 	*ptree_add (char *key, int keylen, void *data, struct ptree *t);
void ptree_remove (struct ptree_node *v); 

struct ptree_node *ptree_head (struct ptree *t);
struct ptree_node *ptree_next (struct ptree_node *v);

struct ptree *ptree_create (void);
void ptree_delete (struct ptree *t);

void     ptree_init(void);
int      ptree_inithead(void **, int);
int      ptree_refines(void *, void *);
struct ptree_node
	*ptree_addmask(void *, int, int),
	*ptree_addroute (void *, void *, struct ptree *,	
			struct ptree_node [2]),
	*ptree_deladdr(void *, void *, struct ptree *),
	*ptree_matchaddr(void *, struct ptree *);

/*
 * Patricia trie API with multipath support
 */
#ifdef PTREE_MPATH
struct route;
struct rtentry;
struct sockaddr;
int	ptree_mpath_capable(struct ptree *);
u_int32_t ptree_mpath_count(struct ptree_node *);
struct rtentry *rt_mpath_matchgate(struct rtentry *, struct sockaddr *);
int rt_mpath_conflict(struct ptree *, struct rtentry *,
    struct sockaddr *);
void rtalloc_mpath_fib(struct route *, u_int32_t, u_int);
#define rtalloc_mpath(_route, _hash) rtalloc_mpath_fib((_route), (_hash), 0)
struct ptree_node *ptree_mpath_lookup(void *, void *,
    struct ptree *);
int rt_mpath_delete(struct rtentry *, struct rtentry *);
int	ptree4_mpath_inithead(void **, int);
int	ptree6_mpath_inithead(void **, int);
#endif /* PTREE_MPATH */
#endif /*_PTREE_H_*/
