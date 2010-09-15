
#ifndef _PTREE_H_
#define _PTREE_H_

#if 0
#ifdef MALLOC_DECLARE
MALLOC_DECLARE(M_RTABLE);
#endif
#endif /*0*/

struct ptree_node {
  //char *key;
  caddr_t rn_key;
  caddr_t rn_mask;
  int   keylen;

  short	rn_bit;
  char	rn_bmask;
  u_char rn_flags;	/* enumerated next */
#define PNF_NOMAL	1
#define PNF_ROOT	2
#define RNF_ACTIVE	4
  struct ptree_node *parent;
  struct ptree_node *child[2];
  void *data;

  int rn_Off;
#ifdef RN_DEBUG
  int rn_info;
  struct ptree_node *rn_twin;
  struct ptree_node *rn_ybro;
#endif
};

#define rn_parent parent
#define rn_left child[0]
#define rn_right child[1]
#define rn_offset rn_Off

#if 0
#define PTREE_LEFT(x) (&(x)->child[0])
#define PTREE_RIGHT(x) (&(x)->child[1])
#endif /*0*/

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


void ptree_node_lock (struct ptree_node *x);
void ptree_node_unlock (struct ptree_node *x);

struct ptree_node *ptree_search (char *key, int keylen, struct ptree *t);
struct ptree_node *ptree_add (char *key, int keylen, void *data, struct ptree *t);
void ptree_remove (struct ptree_node *v);

struct ptree_node *ptree_head (struct ptree *t);
struct ptree_node *ptree_next (struct ptree_node *v);

struct ptree *ptree_create ();
void ptree_delete (struct ptree *t);

#endif /*_PTREE_H_*/

