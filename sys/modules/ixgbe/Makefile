#$FreeBSD: src/sys/modules/ixgbe/Makefile,v 1.6.2.1.2.1 2009/10/25 01:10:29 kensmith Exp $
.PATH:  ${.CURDIR}/../../dev/ixgbe
KMOD    = ixgbe
SRCS    = device_if.h bus_if.h pci_if.h
SRCS    += ixgbe.c
# Shared source
SRCS    += ixgbe_common.c ixgbe_api.c ixgbe_phy.c
SRCS    += ixgbe_82599.c ixgbe_82598.c
CFLAGS+= -I${.CURDIR}/../../dev/ixgbe -DSMP

clean:
	rm -f device_if.h bus_if.h pci_if.h setdef* *_StripErr
	rm -f *.o *.kld *.ko
	rm -f @ machine

.include <bsd.kmod.mk>
