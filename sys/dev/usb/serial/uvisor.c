/*	$NetBSD: uvisor.c,v 1.9 2001/01/23 14:04:14 augustss Exp $	*/
/*      $FreeBSD: src/sys/dev/usb/serial/uvisor.c,v 1.11.2.1.2.1 2009/10/25 01:10:29 kensmith Exp $ */

/* Also already merged from NetBSD:
 *	$NetBSD: uvisor.c,v 1.12 2001/11/13 06:24:57 lukem Exp $
 *	$NetBSD: uvisor.c,v 1.13 2002/02/11 15:11:49 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.14 2002/02/27 23:00:03 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.15 2002/06/16 15:01:31 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.16 2002/07/11 21:14:36 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.17 2002/08/13 11:38:15 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.18 2003/02/05 00:50:14 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.19 2003/02/07 18:12:37 augustss Exp $
 *	$NetBSD: uvisor.c,v 1.20 2003/04/11 01:30:10 simonb Exp $
 */

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Handspring Visor (Palmpilot compatible PDA) driver
 */

#include <sys/stdint.h>
#include <sys/stddef.h>
#include <sys/param.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/bus.h>
#include <sys/linker_set.h>
#include <sys/module.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/condvar.h>
#include <sys/sysctl.h>
#include <sys/sx.h>
#include <sys/unistd.h>
#include <sys/callout.h>
#include <sys/malloc.h>
#include <sys/priv.h>

#include <dev/usb/usb.h>
#include <dev/usb/usbdi.h>
#include <dev/usb/usbdi_util.h>
#include "usbdevs.h"

#define	USB_DEBUG_VAR uvisor_debug
#include <dev/usb/usb_debug.h>
#include <dev/usb/usb_process.h>

#include <dev/usb/serial/usb_serial.h>

#if USB_DEBUG
static int uvisor_debug = 0;

SYSCTL_NODE(_hw_usb, OID_AUTO, uvisor, CTLFLAG_RW, 0, "USB uvisor");
SYSCTL_INT(_hw_usb_uvisor, OID_AUTO, debug, CTLFLAG_RW,
    &uvisor_debug, 0, "Debug level");
#endif

#define	UVISOR_CONFIG_INDEX	0
#define	UVISOR_IFACE_INDEX	0
#define	UVISOR_BUFSIZE       1024	/* bytes */

/* From the Linux driver */
/*
 * UVISOR_REQUEST_BYTES_AVAILABLE asks the visor for the number of bytes that
 * are available to be transfered to the host for the specified endpoint.
 * Currently this is not used, and always returns 0x0001
 */
#define	UVISOR_REQUEST_BYTES_AVAILABLE		0x01

/*
 * UVISOR_CLOSE_NOTIFICATION is set to the device to notify it that the host
 * is now closing the pipe. An empty packet is sent in response.
 */
#define	UVISOR_CLOSE_NOTIFICATION		0x02

/*
 * UVISOR_GET_CONNECTION_INFORMATION is sent by the host during enumeration to
 * get the endpoints used by the connection.
 */
#define	UVISOR_GET_CONNECTION_INFORMATION	0x03

/*
 * UVISOR_GET_CONNECTION_INFORMATION returns data in the following format
 */
#define	UVISOR_MAX_CONN 8
struct uvisor_connection_info {
	uWord	num_ports;
	struct {
		uByte	port_function_id;
		uByte	port;
	} __packed connections[UVISOR_MAX_CONN];
} __packed;

#define	UVISOR_CONNECTION_INFO_SIZE 18

/* struct uvisor_connection_info.connection[x].port defines: */
#define	UVISOR_ENDPOINT_1		0x01
#define	UVISOR_ENDPOINT_2		0x02

/* struct uvisor_connection_info.connection[x].port_function_id defines: */
#define	UVISOR_FUNCTION_GENERIC		0x00
#define	UVISOR_FUNCTION_DEBUGGER	0x01
#define	UVISOR_FUNCTION_HOTSYNC		0x02
#define	UVISOR_FUNCTION_CONSOLE		0x03
#define	UVISOR_FUNCTION_REMOTE_FILE_SYS	0x04

/*
 * Unknown PalmOS stuff.
 */
#define	UVISOR_GET_PALM_INFORMATION		0x04
#define	UVISOR_GET_PALM_INFORMATION_LEN		0x44

struct uvisor_palm_connection_info {
	uByte	num_ports;
	uByte	endpoint_numbers_different;
	uWord	reserved1;
	struct {
		uDWord	port_function_id;
		uByte	port;
		uByte	end_point_info;
		uWord	reserved;
	} __packed connections[UVISOR_MAX_CONN];
} __packed;

enum {
	UVISOR_BULK_DT_WR,
	UVISOR_BULK_DT_RD,
	UVISOR_N_TRANSFER,
};

struct uvisor_softc {
	struct ucom_super_softc sc_super_ucom;
	struct ucom_softc sc_ucom;

	struct usb_xfer *sc_xfer[UVISOR_N_TRANSFER];
	struct usb_device *sc_udev;
	struct mtx sc_mtx;

	uint16_t sc_flag;
#define	UVISOR_FLAG_PALM4       0x0001
#define	UVISOR_FLAG_VISOR       0x0002
#define	UVISOR_FLAG_PALM35      0x0004
#define	UVISOR_FLAG_SEND_NOTIFY 0x0008

	uint8_t	sc_iface_no;
	uint8_t	sc_iface_index;
};

/* prototypes */

static device_probe_t uvisor_probe;
static device_attach_t uvisor_attach;
static device_detach_t uvisor_detach;

static usb_callback_t uvisor_write_callback;
static usb_callback_t uvisor_read_callback;

static usb_error_t uvisor_init(struct uvisor_softc *, struct usb_device *,
		    struct usb_config *);
static void	uvisor_cfg_open(struct ucom_softc *);
static void	uvisor_cfg_close(struct ucom_softc *);
static void	uvisor_start_read(struct ucom_softc *);
static void	uvisor_stop_read(struct ucom_softc *);
static void	uvisor_start_write(struct ucom_softc *);
static void	uvisor_stop_write(struct ucom_softc *);

static const struct usb_config uvisor_config[UVISOR_N_TRANSFER] = {

	[UVISOR_BULK_DT_WR] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_OUT,
		.bufsize = UVISOR_BUFSIZE,	/* bytes */
		.flags = {.pipe_bof = 1,.force_short_xfer = 1,},
		.callback = &uvisor_write_callback,
	},

	[UVISOR_BULK_DT_RD] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.bufsize = UVISOR_BUFSIZE,	/* bytes */
		.flags = {.pipe_bof = 1,.short_xfer_ok = 1,},
		.callback = &uvisor_read_callback,
	},
};

static const struct ucom_callback uvisor_callback = {
	.ucom_cfg_open = &uvisor_cfg_open,
	.ucom_cfg_close = &uvisor_cfg_close,
	.ucom_start_read = &uvisor_start_read,
	.ucom_stop_read = &uvisor_stop_read,
	.ucom_start_write = &uvisor_start_write,
	.ucom_stop_write = &uvisor_stop_write,
};

static device_method_t uvisor_methods[] = {
	DEVMETHOD(device_probe, uvisor_probe),
	DEVMETHOD(device_attach, uvisor_attach),
	DEVMETHOD(device_detach, uvisor_detach),
	{0, 0}
};

static devclass_t uvisor_devclass;

static driver_t uvisor_driver = {
	.name = "uvisor",
	.methods = uvisor_methods,
	.size = sizeof(struct uvisor_softc),
};

DRIVER_MODULE(uvisor, uhub, uvisor_driver, uvisor_devclass, NULL, 0);
MODULE_DEPEND(uvisor, ucom, 1, 1, 1);
MODULE_DEPEND(uvisor, usb, 1, 1, 1);

static const struct usb_device_id uvisor_devs[] = {
	{USB_VPI(USB_VENDOR_ACEECA, USB_PRODUCT_ACEECA_MEZ1000, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_GARMIN, USB_PRODUCT_GARMIN_IQUE_3600, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_FOSSIL, USB_PRODUCT_FOSSIL_WRISTPDA, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_HANDSPRING, USB_PRODUCT_HANDSPRING_VISOR, UVISOR_FLAG_VISOR)},
	{USB_VPI(USB_VENDOR_HANDSPRING, USB_PRODUCT_HANDSPRING_TREO, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_HANDSPRING, USB_PRODUCT_HANDSPRING_TREO600, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_M500, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_M505, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_M515, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_I705, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_M125, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_M130, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_TUNGSTEN_Z, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_TUNGSTEN_T, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_ZIRE, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_PALM, USB_PRODUCT_PALM_ZIRE31, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_SAMSUNG, USB_PRODUCT_SAMSUNG_I500, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_40, 0)},
	{USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_41, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_S360, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_NX60, UVISOR_FLAG_PALM4)},
	{USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_35, UVISOR_FLAG_PALM35)},
/*  {USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_25, UVISOR_FLAG_PALM4 )}, */
	{USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_TJ37, UVISOR_FLAG_PALM4)},
/*  {USB_VPI(USB_VENDOR_SONY, USB_PRODUCT_SONY_CLIE_TH55, UVISOR_FLAG_PALM4 )}, See PR 80935 */
	{USB_VPI(USB_VENDOR_TAPWAVE, USB_PRODUCT_TAPWAVE_ZODIAC, UVISOR_FLAG_PALM4)},
};

static int
uvisor_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	if (uaa->usb_mode != USB_MODE_HOST) {
		return (ENXIO);
	}
	if (uaa->info.bConfigIndex != UVISOR_CONFIG_INDEX) {
		return (ENXIO);
	}
	if (uaa->info.bIfaceIndex != UVISOR_IFACE_INDEX) {
		return (ENXIO);
	}
	return (usbd_lookup_id_by_uaa(uvisor_devs, sizeof(uvisor_devs), uaa));
}

static int
uvisor_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uvisor_softc *sc = device_get_softc(dev);
	struct usb_config uvisor_config_copy[UVISOR_N_TRANSFER];
	int error;

	DPRINTF("sc=%p\n", sc);
	bcopy(uvisor_config, uvisor_config_copy,
	    sizeof(uvisor_config_copy));
	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "uvisor", NULL, MTX_DEF);

	sc->sc_udev = uaa->device;

	/* configure the device */

	sc->sc_flag = USB_GET_DRIVER_INFO(uaa);
	sc->sc_iface_no = uaa->info.bIfaceNum;
	sc->sc_iface_index = UVISOR_IFACE_INDEX;

	error = uvisor_init(sc, uaa->device, uvisor_config_copy);

	if (error) {
		DPRINTF("init failed, error=%s\n",
		    usbd_errstr(error));
		goto detach;
	}
	error = usbd_transfer_setup(uaa->device, &sc->sc_iface_index,
	    sc->sc_xfer, uvisor_config_copy, UVISOR_N_TRANSFER,
	    sc, &sc->sc_mtx);
	if (error) {
		DPRINTF("could not allocate all pipes\n");
		goto detach;
	}
	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UVISOR_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UVISOR_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uvisor_callback, &sc->sc_mtx);
	if (error) {
		DPRINTF("ucom_attach failed\n");
		goto detach;
	}
	return (0);

detach:
	uvisor_detach(dev);
	return (ENXIO);
}

static int
uvisor_detach(device_t dev)
{
	struct uvisor_softc *sc = device_get_softc(dev);

	DPRINTF("sc=%p\n", sc);

	ucom_detach(&sc->sc_super_ucom, &sc->sc_ucom, 1);
	usbd_transfer_unsetup(sc->sc_xfer, UVISOR_N_TRANSFER);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}

static usb_error_t
uvisor_init(struct uvisor_softc *sc, struct usb_device *udev, struct usb_config *config)
{
	usb_error_t err = 0;
	struct usb_device_request req;
	struct uvisor_connection_info coninfo;
	struct uvisor_palm_connection_info pconinfo;
	uint16_t actlen;
	uWord wAvail;
	uint8_t buffer[256];

	if (sc->sc_flag & UVISOR_FLAG_VISOR) {
		DPRINTF("getting connection info\n");
		req.bmRequestType = UT_READ_VENDOR_ENDPOINT;
		req.bRequest = UVISOR_GET_CONNECTION_INFORMATION;
		USETW(req.wValue, 0);
		USETW(req.wIndex, 0);
		USETW(req.wLength, UVISOR_CONNECTION_INFO_SIZE);
		err = usbd_do_request_flags(udev, NULL,
		    &req, &coninfo, USB_SHORT_XFER_OK,
		    &actlen, USB_DEFAULT_TIMEOUT);

		if (err) {
			goto done;
		}
	}
#if USB_DEBUG
	if (sc->sc_flag & UVISOR_FLAG_VISOR) {
		uint16_t i, np;
		const char *desc;

		np = UGETW(coninfo.num_ports);
		if (np > UVISOR_MAX_CONN) {
			np = UVISOR_MAX_CONN;
		}
		DPRINTF("Number of ports: %d\n", np);

		for (i = 0; i < np; ++i) {
			switch (coninfo.connections[i].port_function_id) {
			case UVISOR_FUNCTION_GENERIC:
				desc = "Generic";
				break;
			case UVISOR_FUNCTION_DEBUGGER:
				desc = "Debugger";
				break;
			case UVISOR_FUNCTION_HOTSYNC:
				desc = "HotSync";
				break;
			case UVISOR_FUNCTION_REMOTE_FILE_SYS:
				desc = "Remote File System";
				break;
			default:
				desc = "unknown";
				break;
			}
			DPRINTF("Port %d is for %s\n",
			    coninfo.connections[i].port, desc);
		}
	}
#endif

	if (sc->sc_flag & UVISOR_FLAG_PALM4) {
		uint8_t port;

		/* Palm OS 4.0 Hack */
		req.bmRequestType = UT_READ_VENDOR_ENDPOINT;
		req.bRequest = UVISOR_GET_PALM_INFORMATION;
		USETW(req.wValue, 0);
		USETW(req.wIndex, 0);
		USETW(req.wLength, UVISOR_GET_PALM_INFORMATION_LEN);

		err = usbd_do_request_flags
		    (udev, NULL, &req, &pconinfo, USB_SHORT_XFER_OK,
		    &actlen, USB_DEFAULT_TIMEOUT);

		if (err) {
			goto done;
		}
		if (actlen < 12) {
			DPRINTF("too little data\n");
			err = USB_ERR_INVAL;
			goto done;
		}
		if (pconinfo.endpoint_numbers_different) {
			port = pconinfo.connections[0].end_point_info;
			config[0].endpoint = (port & 0xF);	/* output */
			config[1].endpoint = (port >> 4);	/* input */
		} else {
			port = pconinfo.connections[0].port;
			config[0].endpoint = (port & 0xF);	/* output */
			config[1].endpoint = (port & 0xF);	/* input */
		}
#if 0
		req.bmRequestType = UT_READ_VENDOR_ENDPOINT;
		req.bRequest = UVISOR_GET_PALM_INFORMATION;
		USETW(req.wValue, 0);
		USETW(req.wIndex, 0);
		USETW(req.wLength, UVISOR_GET_PALM_INFORMATION_LEN);
		err = usbd_do_request(udev, &req, buffer);
		if (err) {
			goto done;
		}
#endif
	}
	if (sc->sc_flag & UVISOR_FLAG_PALM35) {
		/* get the config number */
		DPRINTF("getting config info\n");
		req.bmRequestType = UT_READ;
		req.bRequest = UR_GET_CONFIG;
		USETW(req.wValue, 0);
		USETW(req.wIndex, 0);
		USETW(req.wLength, 1);

		err = usbd_do_request(udev, NULL, &req, buffer);
		if (err) {
			goto done;
		}
		/* get the interface number */
		DPRINTF("get the interface number\n");
		req.bmRequestType = UT_READ_DEVICE;
		req.bRequest = UR_GET_INTERFACE;
		USETW(req.wValue, 0);
		USETW(req.wIndex, 0);
		USETW(req.wLength, 1);
		err = usbd_do_request(udev, NULL, &req, buffer);
		if (err) {
			goto done;
		}
	}
	DPRINTF("getting available bytes\n");
	req.bmRequestType = UT_READ_VENDOR_ENDPOINT;
	req.bRequest = UVISOR_REQUEST_BYTES_AVAILABLE;
	USETW(req.wValue, 0);
	USETW(req.wIndex, 5);
	USETW(req.wLength, sizeof(wAvail));
	err = usbd_do_request(udev, NULL, &req, &wAvail);
	if (err) {
		goto done;
	}
	DPRINTF("avail=%d\n", UGETW(wAvail));

	DPRINTF("done\n");
done:
	return (err);
}

static void
uvisor_cfg_open(struct ucom_softc *ucom)
{
	return;
}

static void
uvisor_cfg_close(struct ucom_softc *ucom)
{
	struct uvisor_softc *sc = ucom->sc_parent;
	uint8_t buffer[UVISOR_CONNECTION_INFO_SIZE];
	struct usb_device_request req;
	usb_error_t err;

	req.bmRequestType = UT_READ_VENDOR_ENDPOINT;	/* XXX read? */
	req.bRequest = UVISOR_CLOSE_NOTIFICATION;
	USETW(req.wValue, 0);
	USETW(req.wIndex, 0);
	USETW(req.wLength, UVISOR_CONNECTION_INFO_SIZE);

	err = ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom, 
	    &req, buffer, 0, 1000);
	if (err) {
		DPRINTFN(0, "close notification failed, error=%s\n",
		    usbd_errstr(err));
	}
}

static void
uvisor_start_read(struct ucom_softc *ucom)
{
	struct uvisor_softc *sc = ucom->sc_parent;

	usbd_transfer_start(sc->sc_xfer[UVISOR_BULK_DT_RD]);
}

static void
uvisor_stop_read(struct ucom_softc *ucom)
{
	struct uvisor_softc *sc = ucom->sc_parent;

	usbd_transfer_stop(sc->sc_xfer[UVISOR_BULK_DT_RD]);
}

static void
uvisor_start_write(struct ucom_softc *ucom)
{
	struct uvisor_softc *sc = ucom->sc_parent;

	usbd_transfer_start(sc->sc_xfer[UVISOR_BULK_DT_WR]);
}

static void
uvisor_stop_write(struct ucom_softc *ucom)
{
	struct uvisor_softc *sc = ucom->sc_parent;

	usbd_transfer_stop(sc->sc_xfer[UVISOR_BULK_DT_WR]);
}

static void
uvisor_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uvisor_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint32_t actlen;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_SETUP:
	case USB_ST_TRANSFERRED:
tr_setup:
		pc = usbd_xfer_get_frame(xfer, 0);
		if (ucom_get_data(&sc->sc_ucom, pc, 0,
		    UVISOR_BUFSIZE, &actlen)) {

			usbd_xfer_set_frame_len(xfer, 0, actlen);
			usbd_transfer_submit(xfer);
		}
		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}

static void
uvisor_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uvisor_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		pc = usbd_xfer_get_frame(xfer, 0);
		ucom_put_data(&sc->sc_ucom, pc, 0, actlen);

	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}
