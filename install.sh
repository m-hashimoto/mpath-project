#!/bin/tcsh
echo mpath project install...

#set conf1 = "./conf/files.patricia"
#set conf2 = "./conf/options.patrisia"
set conf = "./conf/*"
set kconf = "./i386/conf/PATRICIA"
set cprg = "./net/*.diff"

cp ${conf} /usr/src/sys/conf/
cp ${kconf} /usr/src/sys/i386/conf/
cp ${cprg} /usr/src/sys/net/

cd /usr/src/sys/conf
patch -N < options.i386.diff

cd /usr/src/sys/net
patch -N < route.c.diff
patch -N < route.h.diff

cd /usr/src/sys/i386/conf/
config PATRICIA

cd ../compile/PATRICIA
make cleandepend && make depend
make && make install
