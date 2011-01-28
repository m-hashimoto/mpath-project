/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/midi/mpu_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _mpu_if_h_
#define _mpu_if_h_

/** @brief Unique descriptor for the MPU_INQSIZE() method */
extern struct kobjop_desc mpu_inqsize_desc;
/** @brief A function implementing the MPU_INQSIZE() method */
typedef int mpu_inqsize_t(struct snd_midi *_kobj, void *_cookie);

static __inline int MPU_INQSIZE(struct snd_midi *_kobj, void *_cookie)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_inqsize);
	return ((mpu_inqsize_t *) _m)(_kobj, _cookie);
}

/** @brief Unique descriptor for the MPU_OUTQSIZE() method */
extern struct kobjop_desc mpu_outqsize_desc;
/** @brief A function implementing the MPU_OUTQSIZE() method */
typedef int mpu_outqsize_t(struct snd_midi *_kobj, void *_cookie);

static __inline int MPU_OUTQSIZE(struct snd_midi *_kobj, void *_cookie)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_outqsize);
	return ((mpu_outqsize_t *) _m)(_kobj, _cookie);
}

/** @brief Unique descriptor for the MPU_INIT() method */
extern struct kobjop_desc mpu_init_desc;
/** @brief A function implementing the MPU_INIT() method */
typedef int mpu_init_t(struct snd_midi *_kobj, void *_cookie);

static __inline int MPU_INIT(struct snd_midi *_kobj, void *_cookie)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_init);
	return ((mpu_init_t *) _m)(_kobj, _cookie);
}

/** @brief Unique descriptor for the MPU_CALLBACKP() method */
extern struct kobjop_desc mpu_callbackp_desc;
/** @brief A function implementing the MPU_CALLBACKP() method */
typedef void mpu_callbackp_t(struct snd_midi *_kobj, void *_cookie, int _flags);

static __inline void MPU_CALLBACKP(struct snd_midi *_kobj, void *_cookie,
                                   int _flags)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_callbackp);
	((mpu_callbackp_t *) _m)(_kobj, _cookie, _flags);
}

/** @brief Unique descriptor for the MPU_CALLBACK() method */
extern struct kobjop_desc mpu_callback_desc;
/** @brief A function implementing the MPU_CALLBACK() method */
typedef void mpu_callback_t(struct snd_midi *_kobj, void *_cookie, int _flags);

static __inline void MPU_CALLBACK(struct snd_midi *_kobj, void *_cookie,
                                  int _flags)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_callback);
	((mpu_callback_t *) _m)(_kobj, _cookie, _flags);
}

/** @brief Unique descriptor for the MPU_PROVIDER() method */
extern struct kobjop_desc mpu_provider_desc;
/** @brief A function implementing the MPU_PROVIDER() method */
typedef const char * mpu_provider_t(struct snd_midi *_kobj, void *_cookie);

static __inline const char * MPU_PROVIDER(struct snd_midi *_kobj, void *_cookie)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_provider);
	return ((mpu_provider_t *) _m)(_kobj, _cookie);
}

/** @brief Unique descriptor for the MPU_DESCR() method */
extern struct kobjop_desc mpu_descr_desc;
/** @brief A function implementing the MPU_DESCR() method */
typedef const char * mpu_descr_t(struct snd_midi *_kobj, void *_cookie,
                                 int _verbosity);

static __inline const char * MPU_DESCR(struct snd_midi *_kobj, void *_cookie,
                                       int _verbosity)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_descr);
	return ((mpu_descr_t *) _m)(_kobj, _cookie, _verbosity);
}

/** @brief Unique descriptor for the MPU_UNINIT() method */
extern struct kobjop_desc mpu_uninit_desc;
/** @brief A function implementing the MPU_UNINIT() method */
typedef int mpu_uninit_t(struct snd_midi *_kobj, void *_cookie);

static __inline int MPU_UNINIT(struct snd_midi *_kobj, void *_cookie)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,mpu_uninit);
	return ((mpu_uninit_t *) _m)(_kobj, _cookie);
}

#endif /* _mpu_if_h_ */
