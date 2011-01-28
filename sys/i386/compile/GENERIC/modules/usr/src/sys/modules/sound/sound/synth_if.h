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


#ifndef _synth_if_h_
#define _synth_if_h_

/** @brief Unique descriptor for the SYNTH_KILLNOTE() method */
extern struct kobjop_desc synth_killnote_desc;
/** @brief A function implementing the SYNTH_KILLNOTE() method */
typedef int synth_killnote_t(void /* X */ *_kobj, uint8_t _chan, uint8_t _note,
                             uint8_t _vel);

static __inline int SYNTH_KILLNOTE(void /* X */ *_kobj, uint8_t _chan,
                                   uint8_t _note, uint8_t _vel)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_killnote);
	return ((synth_killnote_t *) _m)(_kobj, _chan, _note, _vel);
}

/** @brief Unique descriptor for the SYNTH_STARTNOTE() method */
extern struct kobjop_desc synth_startnote_desc;
/** @brief A function implementing the SYNTH_STARTNOTE() method */
typedef int synth_startnote_t(void /* X */ *_kobj, uint8_t _voice,
                              uint8_t _note, uint8_t _parm);

static __inline int SYNTH_STARTNOTE(void /* X */ *_kobj, uint8_t _voice,
                                    uint8_t _note, uint8_t _parm)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_startnote);
	return ((synth_startnote_t *) _m)(_kobj, _voice, _note, _parm);
}

/** @brief Unique descriptor for the SYNTH_SETINSTR() method */
extern struct kobjop_desc synth_setinstr_desc;
/** @brief A function implementing the SYNTH_SETINSTR() method */
typedef int synth_setinstr_t(void /* X */ *_kobj, uint8_t _chn,
                             uint16_t _patchno);

static __inline int SYNTH_SETINSTR(void /* X */ *_kobj, uint8_t _chn,
                                   uint16_t _patchno)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_setinstr);
	return ((synth_setinstr_t *) _m)(_kobj, _chn, _patchno);
}

/** @brief Unique descriptor for the SYNTH_HWCONTROL() method */
extern struct kobjop_desc synth_hwcontrol_desc;
/** @brief A function implementing the SYNTH_HWCONTROL() method */
typedef int synth_hwcontrol_t(void /* X */ *_kobj, uint8_t *_event);

static __inline int SYNTH_HWCONTROL(void /* X */ *_kobj, uint8_t *_event)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_hwcontrol);
	return ((synth_hwcontrol_t *) _m)(_kobj, _event);
}

/** @brief Unique descriptor for the SYNTH_AFTERTOUCH() method */
extern struct kobjop_desc synth_aftertouch_desc;
/** @brief A function implementing the SYNTH_AFTERTOUCH() method */
typedef int synth_aftertouch_t(void /* X */ *_kobj, uint8_t _x1, uint8_t _x2);

static __inline int SYNTH_AFTERTOUCH(void /* X */ *_kobj, uint8_t _x1,
                                     uint8_t _x2)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_aftertouch);
	return ((synth_aftertouch_t *) _m)(_kobj, _x1, _x2);
}

/** @brief Unique descriptor for the SYNTH_PANNING() method */
extern struct kobjop_desc synth_panning_desc;
/** @brief A function implementing the SYNTH_PANNING() method */
typedef int synth_panning_t(void /* X */ *_kobj, uint8_t _x1, uint8_t _x2);

static __inline int SYNTH_PANNING(void /* X */ *_kobj, uint8_t _x1, uint8_t _x2)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_panning);
	return ((synth_panning_t *) _m)(_kobj, _x1, _x2);
}

/** @brief Unique descriptor for the SYNTH_CONTROLLER() method */
extern struct kobjop_desc synth_controller_desc;
/** @brief A function implementing the SYNTH_CONTROLLER() method */
typedef int synth_controller_t(void /* X */ *_kobj, uint8_t _x1, uint8_t _x2,
                               uint16_t _x3);

static __inline int SYNTH_CONTROLLER(void /* X */ *_kobj, uint8_t _x1,
                                     uint8_t _x2, uint16_t _x3)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_controller);
	return ((synth_controller_t *) _m)(_kobj, _x1, _x2, _x3);
}

/** @brief Unique descriptor for the SYNTH_VOLUMEMETHOD() method */
extern struct kobjop_desc synth_volumemethod_desc;
/** @brief A function implementing the SYNTH_VOLUMEMETHOD() method */
typedef int synth_volumemethod_t(void /* X */ *_kobj, uint8_t _x1);

static __inline int SYNTH_VOLUMEMETHOD(void /* X */ *_kobj, uint8_t _x1)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_volumemethod);
	return ((synth_volumemethod_t *) _m)(_kobj, _x1);
}

/** @brief Unique descriptor for the SYNTH_BENDER() method */
extern struct kobjop_desc synth_bender_desc;
/** @brief A function implementing the SYNTH_BENDER() method */
typedef int synth_bender_t(void /* X */ *_kobj, uint8_t _voice, uint16_t _bend);

static __inline int SYNTH_BENDER(void /* X */ *_kobj, uint8_t _voice,
                                 uint16_t _bend)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_bender);
	return ((synth_bender_t *) _m)(_kobj, _voice, _bend);
}

/** @brief Unique descriptor for the SYNTH_SETUPVOICE() method */
extern struct kobjop_desc synth_setupvoice_desc;
/** @brief A function implementing the SYNTH_SETUPVOICE() method */
typedef int synth_setupvoice_t(void /* X */ *_kobj, uint8_t _voice,
                               uint8_t _chn);

static __inline int SYNTH_SETUPVOICE(void /* X */ *_kobj, uint8_t _voice,
                                     uint8_t _chn)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_setupvoice);
	return ((synth_setupvoice_t *) _m)(_kobj, _voice, _chn);
}

/** @brief Unique descriptor for the SYNTH_SENDSYSEX() method */
extern struct kobjop_desc synth_sendsysex_desc;
/** @brief A function implementing the SYNTH_SENDSYSEX() method */
typedef int synth_sendsysex_t(void /* X */ *_kobj, void *_buf, size_t _len);

static __inline int SYNTH_SENDSYSEX(void /* X */ *_kobj, void *_buf,
                                    size_t _len)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_sendsysex);
	return ((synth_sendsysex_t *) _m)(_kobj, _buf, _len);
}

/** @brief Unique descriptor for the SYNTH_ALLOCVOICE() method */
extern struct kobjop_desc synth_allocvoice_desc;
/** @brief A function implementing the SYNTH_ALLOCVOICE() method */
typedef int synth_allocvoice_t(void /* X */ *_kobj, uint8_t _chn, uint8_t _note,
                               void *_x);

static __inline int SYNTH_ALLOCVOICE(void /* X */ *_kobj, uint8_t _chn,
                                     uint8_t _note, void *_x)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobj)->ops,synth_allocvoice);
	return ((synth_allocvoice_t *) _m)(_kobj, _chn, _note, _x);
}

/** @brief Unique descriptor for the SYNTH_WRITERAW() method */
extern struct kobjop_desc synth_writeraw_desc;
/** @brief A function implementing the SYNTH_WRITERAW() method */
typedef int synth_writeraw_t(void /* X */ *_kobjt, uint8_t *_buf, size_t _len);

static __inline int SYNTH_WRITERAW(void /* X */ *_kobjt, uint8_t *_buf,
                                   size_t _len)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_writeraw);
	return ((synth_writeraw_t *) _m)(_kobjt, _buf, _len);
}

/** @brief Unique descriptor for the SYNTH_RESET() method */
extern struct kobjop_desc synth_reset_desc;
/** @brief A function implementing the SYNTH_RESET() method */
typedef int synth_reset_t(void /* X */ *_kobjt);

static __inline int SYNTH_RESET(void /* X */ *_kobjt)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_reset);
	return ((synth_reset_t *) _m)(_kobjt);
}

/** @brief Unique descriptor for the SYNTH_SHORTNAME() method */
extern struct kobjop_desc synth_shortname_desc;
/** @brief A function implementing the SYNTH_SHORTNAME() method */
typedef char * synth_shortname_t(void /* X */ *_kobjt);

static __inline char * SYNTH_SHORTNAME(void /* X */ *_kobjt)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_shortname);
	return ((synth_shortname_t *) _m)(_kobjt);
}

/** @brief Unique descriptor for the SYNTH_OPEN() method */
extern struct kobjop_desc synth_open_desc;
/** @brief A function implementing the SYNTH_OPEN() method */
typedef int synth_open_t(void /* X */ *_kobjt, void *_sythn, int _mode);

static __inline int SYNTH_OPEN(void /* X */ *_kobjt, void *_sythn, int _mode)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_open);
	return ((synth_open_t *) _m)(_kobjt, _sythn, _mode);
}

/** @brief Unique descriptor for the SYNTH_CLOSE() method */
extern struct kobjop_desc synth_close_desc;
/** @brief A function implementing the SYNTH_CLOSE() method */
typedef int synth_close_t(void /* X */ *_kobjt);

static __inline int SYNTH_CLOSE(void /* X */ *_kobjt)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_close);
	return ((synth_close_t *) _m)(_kobjt);
}

/** @brief Unique descriptor for the SYNTH_QUERY() method */
extern struct kobjop_desc synth_query_desc;
/** @brief A function implementing the SYNTH_QUERY() method */
typedef int synth_query_t(void /* X */ *_kobjt);

static __inline int SYNTH_QUERY(void /* X */ *_kobjt)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_query);
	return ((synth_query_t *) _m)(_kobjt);
}

/** @brief Unique descriptor for the SYNTH_INSYNC() method */
extern struct kobjop_desc synth_insync_desc;
/** @brief A function implementing the SYNTH_INSYNC() method */
typedef int synth_insync_t(void /* X */ *_kobjt);

static __inline int SYNTH_INSYNC(void /* X */ *_kobjt)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kobjt)->ops,synth_insync);
	return ((synth_insync_t *) _m)(_kobjt);
}

/** @brief Unique descriptor for the SYNTH_ALLOC() method */
extern struct kobjop_desc synth_alloc_desc;
/** @brief A function implementing the SYNTH_ALLOC() method */
typedef int synth_alloc_t(void /* x */ *_kbojt, uint8_t _chn, uint8_t _note);

static __inline int SYNTH_ALLOC(void /* x */ *_kbojt, uint8_t _chn,
                                uint8_t _note)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_kbojt)->ops,synth_alloc);
	return ((synth_alloc_t *) _m)(_kbojt, _chn, _note);
}

#endif /* _synth_if_h_ */
