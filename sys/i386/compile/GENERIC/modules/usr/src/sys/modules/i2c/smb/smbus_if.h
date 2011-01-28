/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/smbus/smbus_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _smbus_if_h_
#define _smbus_if_h_

/** @brief Unique descriptor for the SMBUS_INTR() method */
extern struct kobjop_desc smbus_intr_desc;
/** @brief A function implementing the SMBUS_INTR() method */
typedef void smbus_intr_t(device_t dev, u_char devaddr, char low, char high,
                          int error);

static __inline void SMBUS_INTR(device_t dev, u_char devaddr, char low,
                                char high, int error)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_intr);
	((smbus_intr_t *) _m)(dev, devaddr, low, high, error);
}

/** @brief Unique descriptor for the SMBUS_CALLBACK() method */
extern struct kobjop_desc smbus_callback_desc;
/** @brief A function implementing the SMBUS_CALLBACK() method */
typedef int smbus_callback_t(device_t dev, int index, void *data);

static __inline int SMBUS_CALLBACK(device_t dev, int index, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_callback);
	return ((smbus_callback_t *) _m)(dev, index, data);
}

/** @brief Unique descriptor for the SMBUS_QUICK() method */
extern struct kobjop_desc smbus_quick_desc;
/** @brief A function implementing the SMBUS_QUICK() method */
typedef int smbus_quick_t(device_t dev, u_char slave, int how);

static __inline int SMBUS_QUICK(device_t dev, u_char slave, int how)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_quick);
	return ((smbus_quick_t *) _m)(dev, slave, how);
}

/** @brief Unique descriptor for the SMBUS_SENDB() method */
extern struct kobjop_desc smbus_sendb_desc;
/** @brief A function implementing the SMBUS_SENDB() method */
typedef int smbus_sendb_t(device_t dev, u_char slave, char byte);

static __inline int SMBUS_SENDB(device_t dev, u_char slave, char byte)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_sendb);
	return ((smbus_sendb_t *) _m)(dev, slave, byte);
}

/** @brief Unique descriptor for the SMBUS_RECVB() method */
extern struct kobjop_desc smbus_recvb_desc;
/** @brief A function implementing the SMBUS_RECVB() method */
typedef int smbus_recvb_t(device_t dev, u_char slave, char *byte);

static __inline int SMBUS_RECVB(device_t dev, u_char slave, char *byte)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_recvb);
	return ((smbus_recvb_t *) _m)(dev, slave, byte);
}

/** @brief Unique descriptor for the SMBUS_WRITEB() method */
extern struct kobjop_desc smbus_writeb_desc;
/** @brief A function implementing the SMBUS_WRITEB() method */
typedef int smbus_writeb_t(device_t dev, u_char slave, char cmd, char byte);

static __inline int SMBUS_WRITEB(device_t dev, u_char slave, char cmd,
                                 char byte)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_writeb);
	return ((smbus_writeb_t *) _m)(dev, slave, cmd, byte);
}

/** @brief Unique descriptor for the SMBUS_WRITEW() method */
extern struct kobjop_desc smbus_writew_desc;
/** @brief A function implementing the SMBUS_WRITEW() method */
typedef int smbus_writew_t(device_t dev, u_char slave, char cmd, short word);

static __inline int SMBUS_WRITEW(device_t dev, u_char slave, char cmd,
                                 short word)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_writew);
	return ((smbus_writew_t *) _m)(dev, slave, cmd, word);
}

/** @brief Unique descriptor for the SMBUS_READB() method */
extern struct kobjop_desc smbus_readb_desc;
/** @brief A function implementing the SMBUS_READB() method */
typedef int smbus_readb_t(device_t dev, u_char slave, char cmd, char *byte);

static __inline int SMBUS_READB(device_t dev, u_char slave, char cmd,
                                char *byte)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_readb);
	return ((smbus_readb_t *) _m)(dev, slave, cmd, byte);
}

/** @brief Unique descriptor for the SMBUS_READW() method */
extern struct kobjop_desc smbus_readw_desc;
/** @brief A function implementing the SMBUS_READW() method */
typedef int smbus_readw_t(device_t dev, u_char slave, char cmd, short *word);

static __inline int SMBUS_READW(device_t dev, u_char slave, char cmd,
                                short *word)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_readw);
	return ((smbus_readw_t *) _m)(dev, slave, cmd, word);
}

/** @brief Unique descriptor for the SMBUS_PCALL() method */
extern struct kobjop_desc smbus_pcall_desc;
/** @brief A function implementing the SMBUS_PCALL() method */
typedef int smbus_pcall_t(device_t dev, u_char slave, char cmd, short sdata,
                          short *rdata);

static __inline int SMBUS_PCALL(device_t dev, u_char slave, char cmd,
                                short sdata, short *rdata)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_pcall);
	return ((smbus_pcall_t *) _m)(dev, slave, cmd, sdata, rdata);
}

/** @brief Unique descriptor for the SMBUS_BWRITE() method */
extern struct kobjop_desc smbus_bwrite_desc;
/** @brief A function implementing the SMBUS_BWRITE() method */
typedef int smbus_bwrite_t(device_t dev, u_char slave, char cmd, u_char count,
                           char *buf);

static __inline int SMBUS_BWRITE(device_t dev, u_char slave, char cmd,
                                 u_char count, char *buf)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_bwrite);
	return ((smbus_bwrite_t *) _m)(dev, slave, cmd, count, buf);
}

/** @brief Unique descriptor for the SMBUS_BREAD() method */
extern struct kobjop_desc smbus_bread_desc;
/** @brief A function implementing the SMBUS_BREAD() method */
typedef int smbus_bread_t(device_t dev, u_char slave, char cmd, u_char *count,
                          char *buf);

static __inline int SMBUS_BREAD(device_t dev, u_char slave, char cmd,
                                u_char *count, char *buf)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,smbus_bread);
	return ((smbus_bread_t *) _m)(dev, slave, cmd, count, buf);
}

#endif /* _smbus_if_h_ */
