/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/pcm/ac97_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _ac97_if_h_
#define _ac97_if_h_

/** @brief Unique descriptor for the AC97_INIT() method */
extern struct kobjop_desc ac97_init_desc;
/** @brief A function implementing the AC97_INIT() method */
typedef u_int32_t ac97_init_t(kobj_t obj, void *devinfo);

static __inline u_int32_t AC97_INIT(kobj_t obj, void *devinfo)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,ac97_init);
	return ((ac97_init_t *) _m)(obj, devinfo);
}

/** @brief Unique descriptor for the AC97_READ() method */
extern struct kobjop_desc ac97_read_desc;
/** @brief A function implementing the AC97_READ() method */
typedef int ac97_read_t(kobj_t obj, void *devinfo, int regno);

static __inline int AC97_READ(kobj_t obj, void *devinfo, int regno)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,ac97_read);
	return ((ac97_read_t *) _m)(obj, devinfo, regno);
}

/** @brief Unique descriptor for the AC97_WRITE() method */
extern struct kobjop_desc ac97_write_desc;
/** @brief A function implementing the AC97_WRITE() method */
typedef int ac97_write_t(kobj_t obj, void *devinfo, int regno, u_int32_t data);

static __inline int AC97_WRITE(kobj_t obj, void *devinfo, int regno,
                               u_int32_t data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)obj)->ops,ac97_write);
	return ((ac97_write_t *) _m)(obj, devinfo, regno, data);
}

#endif /* _ac97_if_h_ */
