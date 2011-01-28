/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/sound/midi/synth_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include "synth_if.h"

#include <sys/systm.h>


synth_killnote_t nokillnote;
synth_startnote_t nostartnote;
synth_setinstr_t nosetinstr;
synth_hwcontrol_t nohwcontrol;
synth_aftertouch_t noaftertouch;
synth_panning_t nopanning;
synth_controller_t nocontroller;
synth_volumemethod_t novolumemethod;
synth_bender_t nobender;
synth_setupvoice_t nosetupvoice;
synth_sendsysex_t nosendsysex;
synth_allocvoice_t noallocvoice;
synth_writeraw_t nowriteraw;
synth_reset_t noreset;
synth_shortname_t noshortname;
synth_open_t noopen;
synth_close_t noclose;
synth_query_t noquery;
synth_insync_t noinsync;
synth_alloc_t noalloc;

    int
	nokillnote(void *_kobj, uint8_t _chn, uint8_t _note, uint8_t _vel)
	{
	    printf("nokillnote\n");
	    return 0;
	}

    int
	noopen(void *_kobj, void *_arg, int mode)
	{
	    printf("noopen\n");
	    return 0;
	}

    int
	noquery(void *_kboj)
	{
	    printf("noquery\n");
	    return 0;
	}

    int
	nostartnote(void *_kb, uint8_t _voice, uint8_t _note, uint8_t _parm)
	{
	    printf("nostartnote\n");
	    return 0;
	}

    int
	nosetinstr(void *_kb, uint8_t _chn, uint16_t _patchno)
	{
	    printf("nosetinstr\n");
	    return 0;
	}

    int
	nohwcontrol(void *_kb, uint8_t *_event)
	{
	    printf("nohwcontrol\n");
	    return 0;
	}

    int 
	noaftertouch ( void /* X */ * _kobj, uint8_t _x1, uint8_t _x2)
	{
	    printf("noaftertouch\n");
	    return 0;
	}

    int
	nopanning ( void /* X */ * _kobj, uint8_t _x1, uint8_t _x2)
	{
	    printf("nopanning\n");
	    return 0;
	}

    int 
	nocontroller ( void /* X */ * _kobj, uint8_t _x1, uint8_t _x2, uint16_t _x3)
	{
	    printf("nocontroller\n");
	    return 0;
	}

    int 
	novolumemethod (
		void /* X */ * _kobj,
		uint8_t _x1)
	{
	    printf("novolumemethod\n");
	    return 0;
	}

    int 
	nobender ( void /* X */ * _kobj, uint8_t _voice, uint16_t _bend)
	{
	    printf("nobender\n");
	    return 0;
	}

    int 
	nosetupvoice ( void /* X */ * _kobj, uint8_t _voice, uint8_t _chn)
	{

	    printf("nosetupvoice\n");
	    return 0;
	}

    int 
	nosendsysex ( void /* X */ * _kobj, void * _buf, size_t _len)
	{
	    printf("nosendsysex\n");
	    return 0;
	}

    int 
	noallocvoice ( void /* X */ * _kobj, uint8_t _chn, uint8_t _note, void *_x)
	{
	    printf("noallocvoice\n");
	    return 0;
	}

    int 
	nowriteraw ( void /* X */ * _kobjt, uint8_t * _buf, size_t _len)
	{
	    printf("nowriteraw\n");
	    return 1;
	}

    int 
	noreset ( void /* X */ * _kobjt)
	{

	    printf("noreset\n");
	    return 0;
	}

    char *
	noshortname (void /* X */ * _kobjt)
	{
	    printf("noshortname\n");
	    return "noshortname";
	}

    int 
	noclose ( void /* X */ * _kobjt)
	{

	    printf("noclose\n");
	    return 0;
	}

    int
	noinsync (void /* X */ * _kobjt)
	{

	    printf("noinsync\n");
	    return 0;
	}

    int 
	noalloc ( void /* x */ * _kbojt, uint8_t _chn, uint8_t _note)
	{
	    printf("noalloc\n");
	    return 0;
	}

struct kobj_method synth_killnote_method_default = {
	&synth_killnote_desc, (kobjop_t) nokillnote
};

struct kobjop_desc synth_killnote_desc = {
	0, &synth_killnote_method_default
};

struct kobj_method synth_startnote_method_default = {
	&synth_startnote_desc, (kobjop_t) nostartnote
};

struct kobjop_desc synth_startnote_desc = {
	0, &synth_startnote_method_default
};

struct kobj_method synth_setinstr_method_default = {
	&synth_setinstr_desc, (kobjop_t) nosetinstr
};

struct kobjop_desc synth_setinstr_desc = {
	0, &synth_setinstr_method_default
};

struct kobj_method synth_hwcontrol_method_default = {
	&synth_hwcontrol_desc, (kobjop_t) nohwcontrol
};

struct kobjop_desc synth_hwcontrol_desc = {
	0, &synth_hwcontrol_method_default
};

struct kobj_method synth_aftertouch_method_default = {
	&synth_aftertouch_desc, (kobjop_t) noaftertouch
};

struct kobjop_desc synth_aftertouch_desc = {
	0, &synth_aftertouch_method_default
};

struct kobj_method synth_panning_method_default = {
	&synth_panning_desc, (kobjop_t) nopanning
};

struct kobjop_desc synth_panning_desc = {
	0, &synth_panning_method_default
};

struct kobj_method synth_controller_method_default = {
	&synth_controller_desc, (kobjop_t) nocontroller
};

struct kobjop_desc synth_controller_desc = {
	0, &synth_controller_method_default
};

struct kobj_method synth_volumemethod_method_default = {
	&synth_volumemethod_desc, (kobjop_t) novolumemethod
};

struct kobjop_desc synth_volumemethod_desc = {
	0, &synth_volumemethod_method_default
};

struct kobj_method synth_bender_method_default = {
	&synth_bender_desc, (kobjop_t) nobender
};

struct kobjop_desc synth_bender_desc = {
	0, &synth_bender_method_default
};

struct kobj_method synth_setupvoice_method_default = {
	&synth_setupvoice_desc, (kobjop_t) nosetupvoice
};

struct kobjop_desc synth_setupvoice_desc = {
	0, &synth_setupvoice_method_default
};

struct kobj_method synth_sendsysex_method_default = {
	&synth_sendsysex_desc, (kobjop_t) nosendsysex
};

struct kobjop_desc synth_sendsysex_desc = {
	0, &synth_sendsysex_method_default
};

struct kobj_method synth_allocvoice_method_default = {
	&synth_allocvoice_desc, (kobjop_t) noallocvoice
};

struct kobjop_desc synth_allocvoice_desc = {
	0, &synth_allocvoice_method_default
};

struct kobj_method synth_writeraw_method_default = {
	&synth_writeraw_desc, (kobjop_t) nowriteraw
};

struct kobjop_desc synth_writeraw_desc = {
	0, &synth_writeraw_method_default
};

struct kobj_method synth_reset_method_default = {
	&synth_reset_desc, (kobjop_t) noreset
};

struct kobjop_desc synth_reset_desc = {
	0, &synth_reset_method_default
};

struct kobj_method synth_shortname_method_default = {
	&synth_shortname_desc, (kobjop_t) noshortname
};

struct kobjop_desc synth_shortname_desc = {
	0, &synth_shortname_method_default
};

struct kobj_method synth_open_method_default = {
	&synth_open_desc, (kobjop_t) noopen
};

struct kobjop_desc synth_open_desc = {
	0, &synth_open_method_default
};

struct kobj_method synth_close_method_default = {
	&synth_close_desc, (kobjop_t) noclose
};

struct kobjop_desc synth_close_desc = {
	0, &synth_close_method_default
};

struct kobj_method synth_query_method_default = {
	&synth_query_desc, (kobjop_t) noquery
};

struct kobjop_desc synth_query_desc = {
	0, &synth_query_method_default
};

struct kobj_method synth_insync_method_default = {
	&synth_insync_desc, (kobjop_t) noinsync
};

struct kobjop_desc synth_insync_desc = {
	0, &synth_insync_method_default
};

struct kobj_method synth_alloc_method_default = {
	&synth_alloc_desc, (kobjop_t) noalloc
};

struct kobjop_desc synth_alloc_desc = {
	0, &synth_alloc_method_default
};

