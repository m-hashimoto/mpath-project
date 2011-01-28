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

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/bus.h>
#include "smbus_if.h"

struct kobj_method smbus_intr_method_default = {
	&smbus_intr_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_intr_desc = {
	0, &smbus_intr_method_default
};

struct kobj_method smbus_callback_method_default = {
	&smbus_callback_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_callback_desc = {
	0, &smbus_callback_method_default
};

struct kobj_method smbus_quick_method_default = {
	&smbus_quick_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_quick_desc = {
	0, &smbus_quick_method_default
};

struct kobj_method smbus_sendb_method_default = {
	&smbus_sendb_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_sendb_desc = {
	0, &smbus_sendb_method_default
};

struct kobj_method smbus_recvb_method_default = {
	&smbus_recvb_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_recvb_desc = {
	0, &smbus_recvb_method_default
};

struct kobj_method smbus_writeb_method_default = {
	&smbus_writeb_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_writeb_desc = {
	0, &smbus_writeb_method_default
};

struct kobj_method smbus_writew_method_default = {
	&smbus_writew_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_writew_desc = {
	0, &smbus_writew_method_default
};

struct kobj_method smbus_readb_method_default = {
	&smbus_readb_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_readb_desc = {
	0, &smbus_readb_method_default
};

struct kobj_method smbus_readw_method_default = {
	&smbus_readw_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_readw_desc = {
	0, &smbus_readw_method_default
};

struct kobj_method smbus_pcall_method_default = {
	&smbus_pcall_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_pcall_desc = {
	0, &smbus_pcall_method_default
};

struct kobj_method smbus_bwrite_method_default = {
	&smbus_bwrite_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_bwrite_desc = {
	0, &smbus_bwrite_method_default
};

struct kobj_method smbus_bread_method_default = {
	&smbus_bread_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc smbus_bread_desc = {
	0, &smbus_bread_method_default
};

