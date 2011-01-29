#!/bin/tcsh
if ( `whoami` != "root" ) then 	
echo "This shellscript must be run by user root." 
exit
endif

echo mpath netstat uninstall...

# remove include file
cd /usr/include/net
mv route.h.org route.h
rm /usr/include/net/ptree.h
rm /usr/include/net/ptree_mpath.h

# repatch
cd /usr/src/usr.bin/netstat
patch -R < route.c.diff

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
