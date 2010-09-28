#!/bin/tcsh
echo uninstall mpath project...

cd /usr/src/sys/conf
patch -R < files.diff
patch -R < options.i386.diff
rm files.diff options.i386.diff

cd /usr/src/sys/net
patch -R < if.c.diff
patch -R < if_clone.c.diff
patch -R < rtsock.c.diff
patch -R < route.c.diff
patch -R < route.h.diff
rm ptree.c ptree_mpath.c ptree.h
rm *.diff

cd /usr/src/sys/netinet
patch -R < in_rmx.c.diff
patch -R < ip_fw.h.diff
rm *.diff
cd ipfw
patch -R < ip_fw2.c.diff
rm *.diff

cd /usr/src/sys/netinet6
patch -R < in6_ifattach.c.diff
patch -R < in6_proto.c.diff
patch -R < in6_rmx.c.diff
patch -R < nd6_rtr.c.diff
rm *.diff

cd /usr/src/sys/contrib/ipfilter/netinet/
patch -R < ip_pool.h.diff
patch -R < ip_pool.c.diff
rm *.diff

cd /usr/src/sys/i386/conf/
rm PATRICIA
#config GENERIC

#cd ../compile/GENERIC
#make cleandepend && make depend
#make && make install
