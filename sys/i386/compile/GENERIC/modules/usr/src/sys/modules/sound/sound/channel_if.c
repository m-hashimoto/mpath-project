/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/pcm/channel_if.m
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
#include "channel_if.h"



	static int
	channel_noreset(kobj_t obj, void *data)
	{
		return 0;
	}

	static int
	channel_noresetdone(kobj_t obj, void *data)
	{
		return 0;
	}

	static int
	channel_nofree(kobj_t obj, void *data)
	{
		return 1;
	}

	static u_int32_t
	channel_nogetptr(kobj_t obj, void *data)
	{
		return 0;
	}

	static int
	channel_nonotify(kobj_t obj, void *data, u_int32_t changed)
	{
		return 0;
	}

	static int
	channel_nogetpeaks(kobj_t obj, void *data, int *lpeak, int *rpeak)
	{
		return -1;
	}

	static int
	channel_nogetrates(kobj_t obj, void *data, int **rates)
	{
		*rates = NULL;
		return 0;
	}

	static int
	channel_nosetfragments(kobj_t obj, void *data, u_int32_t blocksize, u_int32_t blockcount)
	{
		return ENOTSUP;
	}

	static struct pcmchan_matrix *
	channel_nogetmatrix(kobj_t obj, void *data, u_int32_t format)
	{
		format = feeder_matrix_default_format(format);
		return (feeder_matrix_format_map(format));
	}

	static int
	channel_nosetmatrix(kobj_t obj, void *data, struct pcmchan_matrix *m)
	{
		return ENOTSUP;
	}

struct kobj_method channel_init_method_default = {
	&channel_init_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc channel_init_desc = {
	0, &channel_init_method_default
};

struct kobj_method channel_free_method_default = {
	&channel_free_desc, (kobjop_t) channel_nofree
};

struct kobjop_desc channel_free_desc = {
	0, &channel_free_method_default
};

struct kobj_method channel_reset_method_default = {
	&channel_reset_desc, (kobjop_t) channel_noreset
};

struct kobjop_desc channel_reset_desc = {
	0, &channel_reset_method_default
};

struct kobj_method channel_resetdone_method_default = {
	&channel_resetdone_desc, (kobjop_t) channel_noresetdone
};

struct kobjop_desc channel_resetdone_desc = {
	0, &channel_resetdone_method_default
};

struct kobj_method channel_setformat_method_default = {
	&channel_setformat_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc channel_setformat_desc = {
	0, &channel_setformat_method_default
};

struct kobj_method channel_setspeed_method_default = {
	&channel_setspeed_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc channel_setspeed_desc = {
	0, &channel_setspeed_method_default
};

struct kobj_method channel_setblocksize_method_default = {
	&channel_setblocksize_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc channel_setblocksize_desc = {
	0, &channel_setblocksize_method_default
};

struct kobj_method channel_setfragments_method_default = {
	&channel_setfragments_desc, (kobjop_t) channel_nosetfragments
};

struct kobjop_desc channel_setfragments_desc = {
	0, &channel_setfragments_method_default
};

struct kobj_method channel_trigger_method_default = {
	&channel_trigger_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc channel_trigger_desc = {
	0, &channel_trigger_method_default
};

struct kobj_method channel_getptr_method_default = {
	&channel_getptr_desc, (kobjop_t) channel_nogetptr
};

struct kobjop_desc channel_getptr_desc = {
	0, &channel_getptr_method_default
};

struct kobj_method channel_getcaps_method_default = {
	&channel_getcaps_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc channel_getcaps_desc = {
	0, &channel_getcaps_method_default
};

struct kobj_method channel_notify_method_default = {
	&channel_notify_desc, (kobjop_t) channel_nonotify
};

struct kobjop_desc channel_notify_desc = {
	0, &channel_notify_method_default
};

struct kobj_method channel_getpeaks_method_default = {
	&channel_getpeaks_desc, (kobjop_t) channel_nogetpeaks
};

struct kobjop_desc channel_getpeaks_desc = {
	0, &channel_getpeaks_method_default
};

struct kobj_method channel_getrates_method_default = {
	&channel_getrates_desc, (kobjop_t) channel_nogetrates
};

struct kobjop_desc channel_getrates_desc = {
	0, &channel_getrates_method_default
};

struct kobj_method channel_getmatrix_method_default = {
	&channel_getmatrix_desc, (kobjop_t) channel_nogetmatrix
};

struct kobjop_desc channel_getmatrix_desc = {
	0, &channel_getmatrix_method_default
};

struct kobj_method channel_setmatrix_method_default = {
	&channel_setmatrix_desc, (kobjop_t) channel_nosetmatrix
};

struct kobjop_desc channel_setmatrix_desc = {
	0, &channel_setmatrix_method_default
};

