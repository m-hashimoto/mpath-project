#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath project install...

set conf = "./conf/*.diff"
set kconf = "./i386/conf/PATRICIA"
set diff_net = "./net/*.diff"
set diff_netinet = "./netinet/*.diff"
set diff_ipfw = "./netinet/ipfw/*.diff"
set diff_netinet6 = "./netinet6/*.diff"
set diff_ipfilter = "./contrib/ipfilter/netinet/*.diff"
set diff_pf = "./contrib/pf/net/*.diff"
set diff_nfs = "./fs/nfs/*.diff"
set cprg = "./net/*.c"
set head = "./net/*.h"

cp ${conf} /usr/src/sys/conf/
cp ${kconf} /usr/src/sys/i386/conf/
cp ${diff_net} /usr/src/sys/net/
cp ${diff_netinet} /usr/src/sys/netinet/
cp ${diff_ipfw} /usr/src/sys/netinet/ipfw/
cp ${diff_netinet6} /usr/src/sys/netinet6/
cp ${diff_ipfilter} /usr/src/sys/contrib/ipfilter/netinet/
cp ${diff_pf} /usr/src/sys/contrib/pf/net/
cp ${diff_nfs} /usr/src/sys/fs/nfs/
cp ${cprg} /usr/src/sys/net/
cp ${head} /usr/src/sys/net/

cd /usr/src/sys/conf
patch -N < files.diff
patch -N < options.i386.diff

cd /usr/src/sys/net
patch -N < if.c.diff
patch -N < if_clone.c.diff
patch -N < rtsock.c.diff
patch -N < route.c.diff
patch -N < route.h.diff

cd /usr/src/sys/netinet
patch -N < in_rmx.c.diff
patch -N < ip_fw.h.diff
cd ipfw
patch -N < ip_fw2.c.diff

cd /usr/src/sys/netinet6
patch -N < in6_ifattach.c.diff
patch -N < in6_proto.c.diff
patch -N < in6_rmx.c.diff
patch -N < nd6_rtr.c.diff

cd /usr/src/sys/contrib/ipfilter/netinet/
patch -N < ip_pool.h.diff
patch -N < ip_pool.c.diff
cd /usr/src/sys/contrib/pf/net
patch -N < pf.c.diff
patch -N < pf_table.c.diff
patch -N < pfvar.h.diff

cd /usr/src/sys/fs/nfs/
patch -N < nfsport.h.diff

cd /usr/src/sys/i386/conf/
#config PATRICIA
config -g PATRICIA

cd ../compile/PATRICIA
make cleandepend
make depend
make
#make install
