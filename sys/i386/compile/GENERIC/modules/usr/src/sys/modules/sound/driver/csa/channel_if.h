/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/pcm/channel_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _channel_if_h_
#define _channel_if_h_

/** @brief Unique descriptor for the CHANNEL_INIT() method */
extern struct kobjop_desc channel_init_desc;
/** @brief A function implementing the CHANNEL_INIT() method */
typedef void* channel_init_t(kobj_t obj, void *devinfo, struct snd_dbuf *b,
                             struct pcm_channel *c, int dir);

static __inline void* CHANNEL_INIT(kobj_t obj, void *devinfo,
                                   struct snd_dbuf *b, struct pcm_channel *c,
                                   int dir)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_init);
	return ((channel_init_t *) _m)(obj, devinfo, b, c, dir);
}

/** @brief Unique descriptor for the CHANNEL_FREE() method */
extern struct kobjop_desc channel_free_desc;
/** @brief A function implementing the CHANNEL_FREE() method */
typedef int channel_free_t(kobj_t obj, void *data);

static __inline int CHANNEL_FREE(kobj_t obj, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_free);
	return ((channel_free_t *) _m)(obj, data);
}

/** @brief Unique descriptor for the CHANNEL_RESET() method */
extern struct kobjop_desc channel_reset_desc;
/** @brief A function implementing the CHANNEL_RESET() method */
typedef int channel_reset_t(kobj_t obj, void *data);

static __inline int CHANNEL_RESET(kobj_t obj, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_reset);
	return ((channel_reset_t *) _m)(obj, data);
}

/** @brief Unique descriptor for the CHANNEL_RESETDONE() method */
extern struct kobjop_desc channel_resetdone_desc;
/** @brief A function implementing the CHANNEL_RESETDONE() method */
typedef int channel_resetdone_t(kobj_t obj, void *data);

static __inline int CHANNEL_RESETDONE(kobj_t obj, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_resetdone);
	return ((channel_resetdone_t *) _m)(obj, data);
}

/** @brief Unique descriptor for the CHANNEL_SETFORMAT() method */
extern struct kobjop_desc channel_setformat_desc;
/** @brief A function implementing the CHANNEL_SETFORMAT() method */
typedef int channel_setformat_t(kobj_t obj, void *data, u_int32_t format);

static __inline int CHANNEL_SETFORMAT(kobj_t obj, void *data, u_int32_t format)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_setformat);
	return ((channel_setformat_t *) _m)(obj, data, format);
}

/** @brief Unique descriptor for the CHANNEL_SETSPEED() method */
extern struct kobjop_desc channel_setspeed_desc;
/** @brief A function implementing the CHANNEL_SETSPEED() method */
typedef u_int32_t channel_setspeed_t(kobj_t obj, void *data, u_int32_t speed);

static __inline u_int32_t CHANNEL_SETSPEED(kobj_t obj, void *data,
                                           u_int32_t speed)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_setspeed);
	return ((channel_setspeed_t *) _m)(obj, data, speed);
}

/** @brief Unique descriptor for the CHANNEL_SETBLOCKSIZE() method */
extern struct kobjop_desc channel_setblocksize_desc;
/** @brief A function implementing the CHANNEL_SETBLOCKSIZE() method */
typedef u_int32_t channel_setblocksize_t(kobj_t obj, void *data,
                                         u_int32_t blocksize);

static __inline u_int32_t CHANNEL_SETBLOCKSIZE(kobj_t obj, void *data,
                                               u_int32_t blocksize)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_setblocksize);
	return ((channel_setblocksize_t *) _m)(obj, data, blocksize);
}

/** @brief Unique descriptor for the CHANNEL_SETFRAGMENTS() method */
extern struct kobjop_desc channel_setfragments_desc;
/** @brief A function implementing the CHANNEL_SETFRAGMENTS() method */
typedef int channel_setfragments_t(kobj_t obj, void *data, u_int32_t blocksize,
                                   u_int32_t blockcount);

static __inline int CHANNEL_SETFRAGMENTS(kobj_t obj, void *data,
                                         u_int32_t blocksize,
                                         u_int32_t blockcount)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_setfragments);
	return ((channel_setfragments_t *) _m)(obj, data, blocksize, blockcount);
}

/** @brief Unique descriptor for the CHANNEL_TRIGGER() method */
extern struct kobjop_desc channel_trigger_desc;
/** @brief A function implementing the CHANNEL_TRIGGER() method */
typedef int channel_trigger_t(kobj_t obj, void *data, int go);

static __inline int CHANNEL_TRIGGER(kobj_t obj, void *data, int go)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_trigger);
	return ((channel_trigger_t *) _m)(obj, data, go);
}

/** @brief Unique descriptor for the CHANNEL_GETPTR() method */
extern struct kobjop_desc channel_getptr_desc;
/** @brief A function implementing the CHANNEL_GETPTR() method */
typedef u_int32_t channel_getptr_t(kobj_t obj, void *data);

static __inline u_int32_t CHANNEL_GETPTR(kobj_t obj, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_getptr);
	return ((channel_getptr_t *) _m)(obj, data);
}

/** @brief Unique descriptor for the CHANNEL_GETCAPS() method */
extern struct kobjop_desc channel_getcaps_desc;
/** @brief A function implementing the CHANNEL_GETCAPS() method */
typedef struct pcmchan_caps* channel_getcaps_t(kobj_t obj, void *data);

static __inline struct pcmchan_caps* CHANNEL_GETCAPS(kobj_t obj, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_getcaps);
	return ((channel_getcaps_t *) _m)(obj, data);
}

/** @brief Unique descriptor for the CHANNEL_NOTIFY() method */
extern struct kobjop_desc channel_notify_desc;
/** @brief A function implementing the CHANNEL_NOTIFY() method */
typedef int channel_notify_t(kobj_t obj, void *data, u_int32_t changed);

static __inline int CHANNEL_NOTIFY(kobj_t obj, void *data, u_int32_t changed)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_notify);
	return ((channel_notify_t *) _m)(obj, data, changed);
}

/** @brief Unique descriptor for the CHANNEL_GETPEAKS() method */
extern struct kobjop_desc channel_getpeaks_desc;
/** @brief A function implementing the CHANNEL_GETPEAKS() method */
typedef int channel_getpeaks_t(kobj_t obj, void *data, int *lpeak, int *rpeak);
/**
 * @brief Retrieve channel peak values
 *
 * This function is intended to obtain peak volume values for samples
 * played/recorded on a channel.  Values are on a linear scale from 0 to
 * 32767.  If the channel is monaural, a single value should be recorded
 * in @c lpeak.
 *
 * If hardware support isn't available, the SNDCTL_DSP_GET[IO]PEAKS
 * operation should return EINVAL.  However, we may opt to provide
 * software support that the user may toggle via sysctl/mixext.
 *
 * @param obj	standard kobj object (usually @c channel->methods)
 * @param data	driver-specific data (usually @c channel->devinfo)
 * @param lpeak	pointer to store left peak level
 * @param rpeak	pointer to store right peak level
 *
 * @retval -1	Error; usually operation isn't supported.
 * @retval 0	success
 */

static __inline int CHANNEL_GETPEAKS(kobj_t obj, void *data, int *lpeak,
                                     int *rpeak)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_getpeaks);
	return ((channel_getpeaks_t *) _m)(obj, data, lpeak, rpeak);
}

/** @brief Unique descriptor for the CHANNEL_GETRATES() method */
extern struct kobjop_desc channel_getrates_desc;
/** @brief A function implementing the CHANNEL_GETRATES() method */
typedef int channel_getrates_t(kobj_t obj, void *data, int **rates);
/**
 * @brief Retrieve discrete supported sample rates
 *
 * Some cards operate at fixed rates, and this call is intended to retrieve
 * those rates primarily for when in-kernel rate adjustment is undesirable
 * (e.g., application wants direct DMA access after setting a channel to run
 * "uncooked").
 *
 * The parameter @c rates is a double pointer which will be reset to
 * point to an array of supported sample rates.  The number of elements
 * in the array is returned to the caller.
 *
 * @param obj	standard kobj object (usually @c channel->methods)
 * @param data	driver-specific data (usually @c channel->devinfo)
 * @param rates	rate array pointer
 *
 * @return Number of rates in the array
 */

static __inline int CHANNEL_GETRATES(kobj_t obj, void *data, int **rates)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_getrates);
	return ((channel_getrates_t *) _m)(obj, data, rates);
}

/** @brief Unique descriptor for the CHANNEL_GETMATRIX() method */
extern struct kobjop_desc channel_getmatrix_desc;
/** @brief A function implementing the CHANNEL_GETMATRIX() method */
typedef struct pcmchan_matrix * channel_getmatrix_t(kobj_t obj, void *data,
                                                    u_int32_t format);

static __inline struct pcmchan_matrix * CHANNEL_GETMATRIX(kobj_t obj,
                                                          void *data,
                                                          u_int32_t format)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_getmatrix);
	return ((channel_getmatrix_t *) _m)(obj, data, format);
}

/** @brief Unique descriptor for the CHANNEL_SETMATRIX() method */
extern struct kobjop_desc channel_setmatrix_desc;
/** @brief A function implementing the CHANNEL_SETMATRIX() method */
typedef int channel_setmatrix_t(kobj_t obj, void *data,
                                struct pcmchan_matrix *m);

static __inline int CHANNEL_SETMATRIX(kobj_t obj, void *data,
                                      struct pcmchan_matrix *m)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,channel_setmatrix);
	return ((channel_setmatrix_t *) _m)(obj, data, m);
}

#endif /* _channel_if_h_ */
