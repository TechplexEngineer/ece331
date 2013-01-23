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


