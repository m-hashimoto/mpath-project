# $FreeBSD: src/sys/modules/lmc/Makefile,v 1.3.10.1.2.1 2009/10/25 01:10:29 kensmith Exp $

KMOD  = if_lmc
.PATH: ${.CURDIR}/../../dev/lmc

SRCS  = if_lmc.c if_lmc.h
SRCS += device_if.h bus_if.h pci_if.h
SRCS += opt_inet.h opt_inet6.h
SRCS += opt_netgraph.h
SRCS += opt_global.h
SRCS += opt_bpf.h

opt_inet.h:
	echo "#define INET 1"     > ${.TARGET}
opt_inet6.h:
	echo "#define INET6 0"    > ${.TARGET}
opt_netgraph.h:
	echo "#define NETGRAPH 1" > ${.TARGET}
opt_global.h:
	echo "#define ALTQ 1"     > ${.TARGET}
opt_bpf.h: # FreeBSD-5:
	echo "#define DEV_BPF 1"  > ${.TARGET}

.include <bsd.kmod.mk>
