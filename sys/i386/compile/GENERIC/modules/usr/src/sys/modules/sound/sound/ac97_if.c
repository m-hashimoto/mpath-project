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

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <dev/sound/pcm/sound.h>
#include "ac97_if.h"



	static u_int32_t
	ac97_noinit(kobj_t obj, void *devinfo)
	{
		return 1;
	}


struct kobj_method ac97_init_method_default = {
	&ac97_init_desc, (kobjop_t) ac97_noinit
};

struct kobjop_desc ac97_init_desc = {
	0, &ac97_init_method_default
};

struct kobj_method ac97_read_method_default = {
	&ac97_read_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc ac97_read_desc = {
	0, &ac97_read_method_default
};

struct kobj_method ac97_write_method_default = {
	&ac97_write_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc ac97_write_desc = {
	0, &ac97_write_method_default
};

