/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/scc/scc_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _scc_if_h_
#define _scc_if_h_

/** @brief Unique descriptor for the SCC_ATTACH() method */
extern struct kobjop_desc scc_attach_desc;
/** @brief A function implementing the SCC_ATTACH() method */
typedef int scc_attach_t(struct scc_softc *this, int reset);

static __inline int SCC_ATTACH(struct scc_softc *this, int reset)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)this)->ops,scc_attach);
	return ((scc_attach_t *) _m)(this, reset);
}

/** @brief Unique descriptor for the SCC_ENABLED() method */
extern struct kobjop_desc scc_enabled_desc;
/** @brief A function implementing the SCC_ENABLED() method */
typedef int scc_enabled_t(struct scc_softc *this, struct scc_chan *chan);

static __inline int SCC_ENABLED(struct scc_softc *this, struct scc_chan *chan)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)this)->ops,scc_enabled);
	return ((scc_enabled_t *) _m)(this, chan);
}

/** @brief Unique descriptor for the SCC_ICLEAR() method */
extern struct kobjop_desc scc_iclear_desc;
/** @brief A function implementing the SCC_ICLEAR() method */
typedef int scc_iclear_t(struct scc_softc *this, struct scc_chan *chan);

static __inline int SCC_ICLEAR(struct scc_softc *this, struct scc_chan *chan)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)this)->ops,scc_iclear);
	return ((scc_iclear_t *) _m)(this, chan);
}

/** @brief Unique descriptor for the SCC_IPEND() method */
extern struct kobjop_desc scc_ipend_desc;
/** @brief A function implementing the SCC_IPEND() method */
typedef int scc_ipend_t(struct scc_softc *this);

static __inline int SCC_IPEND(struct scc_softc *this)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)this)->ops,scc_ipend);
	return ((scc_ipend_t *) _m)(this);
}

/** @brief Unique descriptor for the SCC_PROBE() method */
extern struct kobjop_desc scc_probe_desc;
/** @brief A function implementing the SCC_PROBE() method */
typedef int scc_probe_t(struct scc_softc *this);

static __inline int SCC_PROBE(struct scc_softc *this)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)this)->ops,scc_probe);
	return ((scc_probe_t *) _m)(this);
}

#endif /* _scc_if_h_ */
