/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/midi/mpu_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <dev/sound/midi/midi.h>
#include "mpu_if.h"

struct kobj_method mpu_inqsize_method_default = {
	&mpu_inqsize_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_inqsize_desc = {
	0, &mpu_inqsize_method_default
};

struct kobj_method mpu_outqsize_method_default = {
	&mpu_outqsize_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_outqsize_desc = {
	0, &mpu_outqsize_method_default
};

struct kobj_method mpu_init_method_default = {
	&mpu_init_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_init_desc = {
	0, &mpu_init_method_default
};

struct kobj_method mpu_callbackp_method_default = {
	&mpu_callbackp_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_callbackp_desc = {
	0, &mpu_callbackp_method_default
};

struct kobj_method mpu_callback_method_default = {
	&mpu_callback_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_callback_desc = {
	0, &mpu_callback_method_default
};

struct kobj_method mpu_provider_method_default = {
	&mpu_provider_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_provider_desc = {
	0, &mpu_provider_method_default
};

struct kobj_method mpu_descr_method_default = {
	&mpu_descr_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_descr_desc = {
	0, &mpu_descr_method_default
};

struct kobj_method mpu_uninit_method_default = {
	&mpu_uninit_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mpu_uninit_desc = {
	0, &mpu_uninit_method_default
};

