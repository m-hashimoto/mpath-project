#!/bin/tcsh
if ( `whoami` != "root" ) then   
echo "This shellscript must be run by user root." 
exit
endif

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
# debug print
#patch -R < ip_output.c.diff
#
rm *.diff
cd ipfw
patch -R < ip_fw2.c.diff
rm *.diff

cd /usr/src/sys/netinet6
patch -R < in6_ifattach.c.diff
patch -R < in6_proto.c.diff
patch -R < in6_rmx.c.diff
patch -R < nd6_rtr.c.diff
patch -R < in6.c.diff
rm *.diff

cd /usr/src/sys/contrib/ipfilter/netinet/
patch -R < ip_pool.h.diff
patch -R < ip_pool.c.diff
rm *.diff
cd ../../pf/net
patch -R < pf.c.diff
patch -R < pf_table.c.diff
patch -R < pfvar.h.diff
rm *.diff

cd /usr/src/sys/fs/nfs/
patch -R < nfsport.h.diff
rm *.diff

cd /usr/src/sys/i386/conf/
rm PATRICIA
#config GENERIC
#cd ../compile/
#rm -r PATRICIA
#cd GENERIC
#make cleandepend && make depend
#make && make install
#while ( 1 );
#echo -n " Reboot Now? [Yes/No] "
#set reboot = $<
#switch ($reboot)
#case [yY][eE][sS]:
#	reboot
#case [nN][oO]:
#	exit
#default:
#	echo "Type Yes/No."
#endsw
#end
