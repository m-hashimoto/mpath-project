/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/pcm/mixer_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _mixer_if_h_
#define _mixer_if_h_

/** @brief Unique descriptor for the MIXER_INIT() method */
extern struct kobjop_desc mixer_init_desc;
/** @brief A function implementing the MIXER_INIT() method */
typedef int mixer_init_t(struct snd_mixer *m);

static __inline int MIXER_INIT(struct snd_mixer *m)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)m)->ops,mixer_init);
	return ((mixer_init_t *) _m)(m);
}

/** @brief Unique descriptor for the MIXER_REINIT() method */
extern struct kobjop_desc mixer_reinit_desc;
/** @brief A function implementing the MIXER_REINIT() method */
typedef int mixer_reinit_t(struct snd_mixer *m);

static __inline int MIXER_REINIT(struct snd_mixer *m)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)m)->ops,mixer_reinit);
	return ((mixer_reinit_t *) _m)(m);
}

/** @brief Unique descriptor for the MIXER_UNINIT() method */
extern struct kobjop_desc mixer_uninit_desc;
/** @brief A function implementing the MIXER_UNINIT() method */
typedef int mixer_uninit_t(struct snd_mixer *m);

static __inline int MIXER_UNINIT(struct snd_mixer *m)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)m)->ops,mixer_uninit);
	return ((mixer_uninit_t *) _m)(m);
}

/** @brief Unique descriptor for the MIXER_SET() method */
extern struct kobjop_desc mixer_set_desc;
/** @brief A function implementing the MIXER_SET() method */
typedef int mixer_set_t(struct snd_mixer *m, unsigned dev, unsigned left,
                        unsigned right);

static __inline int MIXER_SET(struct snd_mixer *m, unsigned dev, unsigned left,
                              unsigned right)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)m)->ops,mixer_set);
	return ((mixer_set_t *) _m)(m, dev, left, right);
}

/** @brief Unique descriptor for the MIXER_SETRECSRC() method */
extern struct kobjop_desc mixer_setrecsrc_desc;
/** @brief A function implementing the MIXER_SETRECSRC() method */
typedef u_int32_t mixer_setrecsrc_t(struct snd_mixer *m, u_int32_t src);

static __inline u_int32_t MIXER_SETRECSRC(struct snd_mixer *m, u_int32_t src)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)m)->ops,mixer_setrecsrc);
	return ((mixer_setrecsrc_t *) _m)(m, src);
}

#endif /* _mixer_if_h_ */
