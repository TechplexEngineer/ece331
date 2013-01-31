Title: Day 4
Date: 1-24-13
Published: true

# Questions on HW1

	//end is pointer to end of buffer
	uintptr_t p64 
	uint64_t v = (c<<8) | c;
	v = (v<<16) | v;
	v = (v<<32) | v;

	//Alignment
	//mset(m+1, 0, SIZE-1);
	//forloop

	while((void*))p64<end) {
		*p64++=v;
	}

	//size % 8 != 0

	//aslo unroll a loop?

	//segfalt - memory not mapped into address space
	//0 is never mappes, as its null

# Filesystems & C Compiler

## bash completion
`$ complete | more`   
`$ set | more`

----

# Command Line Arguments

	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>

	int main(int argc, char* argv[])
	{
		int i;
		for(i=0; i<argc; i++) {
			printf("%d %s\n", i, argv[i]);
		}
		return 0;
	}

---
# Links
@ see [extfs_links.pdf](./extfs_links.pdf)

1. hard links
	$ touch x
	$ ln x y
	//existing new
	- cannot cross filesystem

2. symbolic links
	$ touch a
	$ ln -s a b
	- can cross filesystems

$ ls -l x y a b

----
# Filesystem
@ see [extfs_links.pdf](./extfs_links.pdf)

$ tail /var/log/syslog //last few lines
$ tailf /var/log/syslog //watches for changes and prits them

$ head file //first few lines

$ mount /dev/sda1 /mnt
### unmount
$ umount /mnt

----
$fdisk rasbian.img
>> p //prints partition table

$mkdir /mnt /mnt1

$ mouunt -o loop,offset=4194304 rasbian.img /mnt
$ mouunt -o loop,offset=62914560 rasbian.img /mnt1

//8190 from fdisk
//8190 * 512 = 4194304

----
# GCC & Compiling

see compiling.pdf



