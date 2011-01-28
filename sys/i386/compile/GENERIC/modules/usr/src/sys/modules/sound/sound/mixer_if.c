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

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <dev/sound/pcm/sound.h>
#include "mixer_if.h"



	static int
	mixer_noreinit(struct snd_mixer *m)
	{
		return 0;
	}


struct kobj_method mixer_init_method_default = {
	&mixer_init_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mixer_init_desc = {
	0, &mixer_init_method_default
};

struct kobj_method mixer_reinit_method_default = {
	&mixer_reinit_desc, (kobjop_t) mixer_noreinit
};

struct kobjop_desc mixer_reinit_desc = {
	0, &mixer_reinit_method_default
};

struct kobj_method mixer_uninit_method_default = {
	&mixer_uninit_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mixer_uninit_desc = {
	0, &mixer_uninit_method_default
};

struct kobj_method mixer_set_method_default = {
	&mixer_set_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mixer_set_desc = {
	0, &mixer_set_method_default
};

struct kobj_method mixer_setrecsrc_method_default = {
	&mixer_setrecsrc_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mixer_setrecsrc_desc = {
	0, &mixer_setrecsrc_method_default
};

