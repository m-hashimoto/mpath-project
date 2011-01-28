/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/libkern/iconv_converter_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _iconv_converter_if_h_
#define _iconv_converter_if_h_

/** @brief Unique descriptor for the ICONV_CONVERTER_OPEN() method */
extern struct kobjop_desc iconv_converter_open_desc;
/** @brief A function implementing the ICONV_CONVERTER_OPEN() method */
typedef int iconv_converter_open_t(struct iconv_converter_class *dcp,
                                   struct iconv_cspair *cspto,
                                   struct iconv_cspair *cspfrom, void **hpp);

static __inline int ICONV_CONVERTER_OPEN(struct iconv_converter_class *dcp,
                                         struct iconv_cspair *cspto,
                                         struct iconv_cspair *cspfrom,
                                         void **hpp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(dcp->ops,iconv_converter_open);
	return ((iconv_converter_open_t *) _m)(dcp, cspto, cspfrom, hpp);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_CLOSE() method */
extern struct kobjop_desc iconv_converter_close_desc;
/** @brief A function implementing the ICONV_CONVERTER_CLOSE() method */
typedef int iconv_converter_close_t(void *handle);

static __inline int ICONV_CONVERTER_CLOSE(void *handle)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)handle)->ops,iconv_converter_close);
	return ((iconv_converter_close_t *) _m)(handle);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_CONV() method */
extern struct kobjop_desc iconv_converter_conv_desc;
/** @brief A function implementing the ICONV_CONVERTER_CONV() method */
typedef int iconv_converter_conv_t(void *handle, const char **inbuf,
                                   size_t *inbytesleft, char **outbuf,
                                   size_t *outbytesleft, int convchar,
                                   int casetype);

static __inline int ICONV_CONVERTER_CONV(void *handle, const char **inbuf,
                                         size_t *inbytesleft, char **outbuf,
                                         size_t *outbytesleft, int convchar,
                                         int casetype)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)handle)->ops,iconv_converter_conv);
	return ((iconv_converter_conv_t *) _m)(handle, inbuf, inbytesleft, outbuf, outbytesleft, convchar, casetype);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_INIT() method */
extern struct kobjop_desc iconv_converter_init_desc;
/** @brief A function implementing the ICONV_CONVERTER_INIT() method */
typedef int iconv_converter_init_t(struct iconv_converter_class *dcp);

static __inline int ICONV_CONVERTER_INIT(struct iconv_converter_class *dcp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(dcp->ops,iconv_converter_init);
	return ((iconv_converter_init_t *) _m)(dcp);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_DONE() method */
extern struct kobjop_desc iconv_converter_done_desc;
/** @brief A function implementing the ICONV_CONVERTER_DONE() method */
typedef int iconv_converter_done_t(struct iconv_converter_class *dcp);

static __inline int ICONV_CONVERTER_DONE(struct iconv_converter_class *dcp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(dcp->ops,iconv_converter_done);
	return ((iconv_converter_done_t *) _m)(dcp);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_NAME() method */
extern struct kobjop_desc iconv_converter_name_desc;
/** @brief A function implementing the ICONV_CONVERTER_NAME() method */
typedef const char * iconv_converter_name_t(struct iconv_converter_class *dcp);

static __inline const char * ICONV_CONVERTER_NAME(struct iconv_converter_class *dcp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(dcp->ops,iconv_converter_name);
	return ((iconv_converter_name_t *) _m)(dcp);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_TOLOWER() method */
extern struct kobjop_desc iconv_converter_tolower_desc;
/** @brief A function implementing the ICONV_CONVERTER_TOLOWER() method */
typedef int iconv_converter_tolower_t(void *handle, int c);

static __inline int ICONV_CONVERTER_TOLOWER(void *handle, int c)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)handle)->ops,iconv_converter_tolower);
	return ((iconv_converter_tolower_t *) _m)(handle, c);
}

/** @brief Unique descriptor for the ICONV_CONVERTER_TOUPPER() method */
extern struct kobjop_desc iconv_converter_toupper_desc;
/** @brief A function implementing the ICONV_CONVERTER_TOUPPER() method */
typedef int iconv_converter_toupper_t(void *handle, int c);

static __inline int ICONV_CONVERTER_TOUPPER(void *handle, int c)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)handle)->ops,iconv_converter_toupper);
	return ((iconv_converter_toupper_t *) _m)(handle, c);
}

#endif /* _iconv_converter_if_h_ */
