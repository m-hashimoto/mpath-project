/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/scc/scc_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/param.h>
#include <sys/bus.h>
#include <machine/bus.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/rman.h>
#include <dev/scc/scc_bfe.h>
#include "scc_if.h"


static int
default_enabled(struct scc_softc *this, struct scc_chan *ch)
{
	return (1);
}

struct kobj_method scc_attach_method_default = {
	&scc_attach_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc scc_attach_desc = {
	0, &scc_attach_method_default
};

struct kobj_method scc_enabled_method_default = {
	&scc_enabled_desc, (kobjop_t) default_enabled
};

struct kobjop_desc scc_enabled_desc = {
	0, &scc_enabled_method_default
};

struct kobj_method scc_iclear_method_default = {
	&scc_iclear_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc scc_iclear_desc = {
	0, &scc_iclear_method_default
};

struct kobj_method scc_ipend_method_default = {
	&scc_ipend_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc scc_ipend_desc = {
	0, &scc_ipend_method_default
};

struct kobj_method scc_probe_method_default = {
	&scc_probe_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc scc_probe_desc = {
	0, &scc_probe_method_default
};

