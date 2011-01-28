/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/iicbus/iicbus_if.m
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
#include <dev/iicbus/iic.h>
#include "iicbus_if.h"

struct kobj_method iicbus_intr_method_default = {
	&iicbus_intr_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_intr_desc = {
	0, &iicbus_intr_method_default
};

struct kobj_method iicbus_callback_method_default = {
	&iicbus_callback_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_callback_desc = {
	0, &iicbus_callback_method_default
};

struct kobj_method iicbus_repeated_start_method_default = {
	&iicbus_repeated_start_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_repeated_start_desc = {
	0, &iicbus_repeated_start_method_default
};

struct kobj_method iicbus_start_method_default = {
	&iicbus_start_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_start_desc = {
	0, &iicbus_start_method_default
};

struct kobj_method iicbus_stop_method_default = {
	&iicbus_stop_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_stop_desc = {
	0, &iicbus_stop_method_default
};

struct kobj_method iicbus_read_method_default = {
	&iicbus_read_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_read_desc = {
	0, &iicbus_read_method_default
};

struct kobj_method iicbus_write_method_default = {
	&iicbus_write_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_write_desc = {
	0, &iicbus_write_method_default
};

struct kobj_method iicbus_reset_method_default = {
	&iicbus_reset_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_reset_desc = {
	0, &iicbus_reset_method_default
};

struct kobj_method iicbus_transfer_method_default = {
	&iicbus_transfer_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iicbus_transfer_desc = {
	0, &iicbus_transfer_method_default
};

