/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   ../../../dev/usb/usb_if.m
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
#include "usb_if.h"

struct kobj_method usb_handle_request_method_default = {
	&usb_handle_request_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc usb_handle_request_desc = {
	0, &usb_handle_request_method_default
};

