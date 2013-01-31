Title: Day 3
Date: 1/22/13
Published: true

# cd
# mkdir junk
# cd junk
# touch * //bash autoquotes
# touch | //since | is special needs to be quotes
# touch \| //now its quoted
# rm -rf * //empties the directory
# rm -rf \* //the file named *

# touch $SHELL //error


#find /etc -iname \*conf 2>/dev/null
//send file descriptor 2(std error) to /dev/null

#ls /etc/udev/rusles.d/*[0-5]*rules

#dpkg -L gcc | wc -l //count the number of lines output

#ls -l /usr/bin | wc -l //count number of files in /usr/bin
wc is word count program

| //redirect stdout to stdin of next program
>  //redirect output(stdout) to file
>> //append
<  //redirect input(stdin)

#dpkg -L gcc> gcclist
#dpkg -L binutils >> gcclist
#fdisk /dev/sda < file


///////////////
// job control
<ctrl>Z  //suspend

#jobs //list jobs
#fg		//bring to foreground
#fg %3	//fg #3 job
#bg 	//send job to background

///////////////
// File Commands
//////////////

//list files
#ls 
#ls -a //shows hidden files too (all)

//Copy files
#cp from to

//Rename & Move files
#mv old new

//Remove
#rm file

//Identify (Seven file types)
#file /usr/bin/gcc 			//symbolic link
#file /bin/ls 				//regular file
#file /dev/null				//character special
#file /dev/mmcblk0			//sticky block special
#file /tmp					//sticky directory
#file /var/run/thd.socket 	//socket
#file /var/run/initctl		//fifo (named pipe)

