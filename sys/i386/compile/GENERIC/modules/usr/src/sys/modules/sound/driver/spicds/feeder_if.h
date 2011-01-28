/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/pcm/feeder_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _feeder_if_h_
#define _feeder_if_h_

/** @brief Unique descriptor for the FEEDER_INIT() method */
extern struct kobjop_desc feeder_init_desc;
/** @brief A function implementing the FEEDER_INIT() method */
typedef int feeder_init_t(struct pcm_feeder* feeder);

static __inline int FEEDER_INIT(struct pcm_feeder* feeder)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)feeder)->ops,feeder_init);
	return ((feeder_init_t *) _m)(feeder);
}

/** @brief Unique descriptor for the FEEDER_FREE() method */
extern struct kobjop_desc feeder_free_desc;
/** @brief A function implementing the FEEDER_FREE() method */
typedef int feeder_free_t(struct pcm_feeder* feeder);

static __inline int FEEDER_FREE(struct pcm_feeder* feeder)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)feeder)->ops,feeder_free);
	return ((feeder_free_t *) _m)(feeder);
}

/** @brief Unique descriptor for the FEEDER_SET() method */
extern struct kobjop_desc feeder_set_desc;
/** @brief A function implementing the FEEDER_SET() method */
typedef int feeder_set_t(struct pcm_feeder* feeder, int what, int value);

static __inline int FEEDER_SET(struct pcm_feeder* feeder, int what, int value)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)feeder)->ops,feeder_set);
	return ((feeder_set_t *) _m)(feeder, what, value);
}

/** @brief Unique descriptor for the FEEDER_GET() method */
extern struct kobjop_desc feeder_get_desc;
/** @brief A function implementing the FEEDER_GET() method */
typedef int feeder_get_t(struct pcm_feeder* feeder, int what);

static __inline int FEEDER_GET(struct pcm_feeder* feeder, int what)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)feeder)->ops,feeder_get);
	return ((feeder_get_t *) _m)(feeder, what);
}

/** @brief Unique descriptor for the FEEDER_FEED() method */
extern struct kobjop_desc feeder_feed_desc;
/** @brief A function implementing the FEEDER_FEED() method */
typedef int feeder_feed_t(struct pcm_feeder* feeder, struct pcm_channel* c,
                          u_int8_t* buffer, u_int32_t count, void* source);

static __inline int FEEDER_FEED(struct pcm_feeder* feeder,
                                struct pcm_channel* c, u_int8_t* buffer,
                                u_int32_t count, void* source)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)feeder)->ops,feeder_feed);
	return ((feeder_feed_t *) _m)(feeder, c, buffer, count, source);
}

#endif /* _feeder_if_h_ */
