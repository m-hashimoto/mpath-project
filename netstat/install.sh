#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath netstat install...

set diff_netstat = "./*.diff"
cp ${diff_netstat} /usr/src/usr.bin/netstat/
# cp include file
set head = "../net/*.h"
set head_diff = "../net/route.h.diff"
cp ${head} /usr/include/net/
cp ${head_diff} /usr/include/net/

cd /usr/include/net/
patch -N < route.h.diff

cd /usr/src/usr.bin/netstat/
patch -N < route.c.diff
make deinstall && make
while ( 1 );
echo -n " Install Now?(netstat) [Yes/No] "
set configure = $<
switch ($configure)
case [yY][eE][sS]:
	make reinstall
	break
case [nN][oO]:
	exit
default:
	echo "Type Yes/No."
endsw
end
