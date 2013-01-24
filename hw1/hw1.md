ECE 331 - HW 1
Blake Bourque

1.) //Copy file from remote server with scp
#scp bbourque@hammer.eece.maine.edu:/usr/linux/public/ece331/fmemset-char.c .


2.) See attached

3.) See attached

4.) //find package containt top
//find where top is installed
# which top
// /usr/bin/top
# dpkg -S /usr/bin/top

//Shortcut: dpkg -S `which top`
// procps: /usr/bin/top

# dpkg -l procps //info about package

//install package
apt-get install procps

5.) 
//udevd lives in:
/sbin/udevd

Udev processes rules on various kernel events, mostly which are related to device access.
Udev is important to have running as without it only statically defined device can be accessed.

6.) Permissions:
a.) chmod g+rx,o+r opamp.m
b.) chmod og+r,u-w


