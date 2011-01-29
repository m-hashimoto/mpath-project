#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath netstat install...

# cp include file
echo include file copying
cd /usr/include/net
cp route.h route.h.org
cp /usr/src/net/ptree.h /usr/include/net/
echo -n .
cp /usr/src/net/ptree_mpath.h /usr/include/net/
echo -n .
cp /usr/src/net/route.h /usr/include/net/
echo .

while ( 1 );
echo -n " Install Now?(netstat) [Yes/No] "
set configure = $<
switch ($configure)
case [yY][eE][sS]:
	make && make install
	break
case [nN][oO]:
	exit
default:
	echo "Type Yes/No."
endsw
end
