
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

struct ptree_node {
  //char *key;
  struct  ptree_mask *rn_mklist;
  caddr_t key;
  caddr_t rn_mask;
  int   keylen;

  short	rn_bit;
  char	rn_bmask;
  u_char rn_flags;	/* enumerated next */
#define RNF_NOMAL	1
#define RNF_ROOT	2
#define RNF_ACTIVE	4
  struct ptree_node *parent;
  struct ptree_node *child[2];
  struct ptree_node *rn_dupendkey;
  void *data;

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
	short   rm_bit;                 /* bit offset; -1-index(netmask) */        char    rm_unused;              /* cf. rn_bmask */
	u_char  rm_flags;               /* cf. rn_flags */
	struct  radix_mask *rm_mklist;  /* more masks to try */
	union   {
		caddr_t rmu_mask;               /* the mask */
		struct  radix_node *rmu_leaf;   /* for normal routes */
	}       rm_rmu;
	int     rm_refs;                /* # of references to this struct */
};

#define rm_mask rm_rmu.rmu_mask
#define rm_leaf rm_rmu.rmu_leaf         /* extra field would make 32 bytes */

struct ptree {
	struct ptree_node *top;
	int	 rnh_addsize;	/* permit, but not require fixed keys */
	int	 rnh_pktsize;   /* permit, but not require fixed keys */
	struct ptree_node rnh_nodes[3]; /* empty tree for comon case */
	int	 rnh_multipath;	/* multipath capable ? */
#ifdef _KERNEL
	struct rwlock rnh_lock; /* locks entire */
#endif
};

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


//void ptree_node_lock (struct ptree_node *x);
//void ptree_node_unlock (struct ptree_node *x);

struct ptree_node *ptree_lookup (char *key, int keylen, struct ptree *t);
struct ptree_node *ptree_search (char *key, int keylen, struct ptree *t);
struct ptree_node *ptree_add (char *key, int keylen, void *data, struct ptree *t);
void ptree_remove (struct ptree_node *v);

struct ptree_node *ptree_head (struct ptree *t);
struct ptree_node *ptree_next (struct ptree_node *v);

struct ptree *ptree_create (void);
void ptree_delete (struct ptree *t);

struct ptree_node *rn_newpair(void *v, int b, struct ptree_node *nodes);

#endif /*_PTREE_H_*/

