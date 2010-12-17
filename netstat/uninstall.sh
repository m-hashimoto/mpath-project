#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath netstat uninstall...

# remove include file
patch -N < route.h.diff
rm /usr/include/net/ptree.h
rm /usr/include/net/ptree_mpath.h

cd /usr/src/usr.bin/netstat/
patch -R < route.c.diff
make && make reinstall
