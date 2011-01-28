/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/iicbus/iicbb_if.m
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
#include "iicbb_if.h"

struct kobj_method iicbb_callback_method_default = {
	&iicbb_callback_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbb_callback_desc = {
	0, &iicbb_callback_method_default
};

struct kobj_method iicbb_setsda_method_default = {
	&iicbb_setsda_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbb_setsda_desc = {
	0, &iicbb_setsda_method_default
};

struct kobj_method iicbb_setscl_method_default = {
	&iicbb_setscl_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbb_setscl_desc = {
	0, &iicbb_setscl_method_default
};

struct kobj_method iicbb_getsda_method_default = {
	&iicbb_getsda_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbb_getsda_desc = {
	0, &iicbb_getsda_method_default
};

struct kobj_method iicbb_getscl_method_default = {
	&iicbb_getscl_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbb_getscl_desc = {
	0, &iicbb_getscl_method_default
};

struct kobj_method iicbb_reset_method_default = {
	&iicbb_reset_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbb_reset_desc = {
	0, &iicbb_reset_method_default
};

