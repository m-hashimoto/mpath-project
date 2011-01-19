#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath netstat install...

set diff_netstat = "./route.c.diff"
cp ${diff_netstat} /usr/src/usr.bin/netstat/
# cp include file
set head_diff = "../net/route.h.diff"
cp ../net/ptree.h /usr/include/net/
cp ../net/ptree_mpath.h /usr/include/net/
cp ${head_diff} /usr/include/net/
# diff patch
cd /usr/include/net/
patch -N < route.h.diff
cd /usr/src/usr.bin/netstat/
patch -N < route.c.diff

make
while ( 1 );
echo -n " Install Now?(netstat) [Yes/No] "
set configure = $<
switch ($configure)
case [yY][eE][sS]:
	make install
	break
case [nN][oO]:
	exit
default:
	echo "Type Yes/No."
endsw
end
