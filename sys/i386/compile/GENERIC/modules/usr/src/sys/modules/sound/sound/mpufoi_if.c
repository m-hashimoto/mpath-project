/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/midi/mpufoi_if.m
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
#include <dev/sound/midi/mpu401.h>
#include "mpufoi_if.h"

struct kobj_method mpufoi_read_method_default = {
	&mpufoi_read_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpufoi_read_desc = {
	0, &mpufoi_read_method_default
};

struct kobj_method mpufoi_write_method_default = {
	&mpufoi_write_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpufoi_write_desc = {
	0, &mpufoi_write_method_default
};

struct kobj_method mpufoi_uninit_method_default = {
	&mpufoi_uninit_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpufoi_uninit_desc = {
	0, &mpufoi_uninit_method_default
};

