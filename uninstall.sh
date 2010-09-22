#!/bin/tcsh
echo uninstall mpath project...

cd /usr/src/sys/conf
patch -R < options.i386.diff

cd /usr/src/sys/net
patch -R < route.c.diff
patch -R < route.h.diff

#cd /usr/src/sys/i386/conf/
#config GENERIC

#cd ../compile/GENERIC
#make cleandepend && make depend
#make && make install
