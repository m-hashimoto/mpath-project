/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/midi/mpufoi_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _mpufoi_if_h_
#define _mpufoi_if_h_

/** @brief Unique descriptor for the MPUFOI_READ() method */
extern struct kobjop_desc mpufoi_read_desc;
/** @brief A function implementing the MPUFOI_READ() method */
typedef unsigned char mpufoi_read_t(struct mpu401 *_kobj, void *_cookie,
                                    int _reg);

static __inline unsigned char MPUFOI_READ(struct mpu401 *_kobj, void *_cookie,
                                          int _reg)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpufoi_read);
	return ((mpufoi_read_t *) _m)(_kobj, _cookie, _reg);
}

/** @brief Unique descriptor for the MPUFOI_WRITE() method */
extern struct kobjop_desc mpufoi_write_desc;
/** @brief A function implementing the MPUFOI_WRITE() method */
typedef void mpufoi_write_t(struct mpu401 *_kobj, void *_cookie, int _reg,
                            unsigned char _d);

static __inline void MPUFOI_WRITE(struct mpu401 *_kobj, void *_cookie, int _reg,
                                  unsigned char _d)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpufoi_write);
	((mpufoi_write_t *) _m)(_kobj, _cookie, _reg, _d);
}

/** @brief Unique descriptor for the MPUFOI_UNINIT() method */
extern struct kobjop_desc mpufoi_uninit_desc;
/** @brief A function implementing the MPUFOI_UNINIT() method */
typedef int mpufoi_uninit_t(struct mpu401 *_kobj, void *_cookie);

static __inline int MPUFOI_UNINIT(struct mpu401 *_kobj, void *_cookie)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpufoi_uninit);
	return ((mpufoi_uninit_t *) _m)(_kobj, _cookie);
}

#endif /* _mpufoi_if_h_ */
