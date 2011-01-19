#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath netstat uninstall...

# remove include file
cd /usr/include/net
patch -R < route.h.diff
rm /usr/include/net/route.h.diff
rm /usr/include/net/ptree.h
rm /usr/include/net/ptree_mpath.h
# reverse patch
cd /usr/src/usr.bin/netstat/
patch -R < route.c.diff
make && make reinstall
