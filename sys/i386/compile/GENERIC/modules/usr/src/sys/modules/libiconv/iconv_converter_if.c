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

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/iconv.h>
#include "iconv_converter_if.h"

struct kobj_method iconv_converter_open_method_default = {
	&iconv_converter_open_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iconv_converter_open_desc = {
	0, &iconv_converter_open_method_default
};

struct kobj_method iconv_converter_close_method_default = {
	&iconv_converter_close_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iconv_converter_close_desc = {
	0, &iconv_converter_close_method_default
};

struct kobj_method iconv_converter_conv_method_default = {
	&iconv_converter_conv_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iconv_converter_conv_desc = {
	0, &iconv_converter_conv_method_default
};

struct kobj_method iconv_converter_init_method_default = {
	&iconv_converter_init_desc, (kobjop_t) iconv_converter_initstub
};

struct kobjop_desc iconv_converter_init_desc = {
	0, &iconv_converter_init_method_default
};

struct kobj_method iconv_converter_done_method_default = {
	&iconv_converter_done_desc, (kobjop_t) iconv_converter_donestub
};

struct kobjop_desc iconv_converter_done_desc = {
	0, &iconv_converter_done_method_default
};

struct kobj_method iconv_converter_name_method_default = {
	&iconv_converter_name_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc iconv_converter_name_desc = {
	0, &iconv_converter_name_method_default
};

struct kobj_method iconv_converter_tolower_method_default = {
	&iconv_converter_tolower_desc, (kobjop_t) iconv_converter_tolowerstub
};

struct kobjop_desc iconv_converter_tolower_desc = {
	0, &iconv_converter_tolower_method_default
};

struct kobj_method iconv_converter_toupper_method_default = {
	&iconv_converter_toupper_desc, (kobjop_t) iconv_converter_tolowerstub
};

struct kobjop_desc iconv_converter_toupper_desc = {
	0, &iconv_converter_toupper_method_default
};

