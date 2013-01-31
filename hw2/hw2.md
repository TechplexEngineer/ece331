## ECE 331 - HW 2 Blake Bourque
### Due: 1/31/2013

@Note: This was written in markdown which compiles to html. The pound `#` is reserved as a keyword in markdown. In the below document `$` is used to indicate a command prompt.
## 1.) Program to count the number of lines in matched (glob) files

	////////////////////////////////////////////////////////////////////////////////
	// ECE 331 - HW2
	// Author: Blake Bourque
	// Date: 1/31/2013
	// Purpose: Count lines in files matched by globs
	// 	demonstrate the use of low level system calls (open, read, close)
	////////////////////////////////////////////////////////////////////////////////

	#include <stdio.h>
	#include <stdlib.h>

	//errors
	#include <errno.h>

	//glob
	#include <string.h>
	#include <glob.h>

	//open
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>

	//read
	#include <unistd.h>

	//size of buffer in bytes (1Mb). Must be less than SSIZE_MAX
	#define BUFF_SIZE 1024

	//closes the file, handles associated errors with perror
	void handleClose(int fd);
	void printHelp(char* prgmName);

	int main(int argc, char* argv[])
	{
		//@note  when running the program, be sure to escape glob characters, or they'll be eval'd by the shell
		//printf("Num Args: %d \n", (argc-1)); //ignore program name
		if(argc == 1) {
			fprintf(stderr, "%s: missing file operand\nTry `%s ?' for more information. \n",argv[0], argv[0]);//@todo: Try again with ? or --h
			return -1;
		}
		if(strcmp(argv[1], "?") == 0) {
			printHelp(argv[0]);
			return -1;
		}
		int i; //Loop control
		glob_t globuff;

		//process the arguments
		for(i=1; i<=(argc -1); i++) { //we'll skip the first arg as its the program name
			//printf("Arg: %s \n", argv[i]);
			
			//parse each glob
			if(i==1)
				glob(argv[i], 0, NULL, &globuff);
			else 
				glob(argv[i], GLOB_APPEND, NULL, &globuff);
		}
		printf("%zd matches.\n", globuff.gl_pathc);
		uint newLines = 0; //total newlines

		for(i=0;i<globuff.gl_pathc; i++) {
			uint fileNewLines =0; //newlines in this file
			//openfile $man 2 open
			int fd = open(globuff.gl_pathv[i], O_RDONLY);
			if(fd == -1) { //error checking
				printf("No fd returned\n");
				perror("open");
				continue; 
			}
			char buff[BUFF_SIZE]; //we could move this outside the loop. In which case we'd have to clear it each time.
			//read buffer of data
			ssize_t amt = read(fd, buff, BUFF_SIZE);
			while(amt > 0) {
				int i=0; //loop control variable

				//count newlines in buffer
				for (i=0; i<amt && buff[i] != '\0'; i++) {
					if(buff[i] == '\n')
						fileNewLines++;
				}
				
				//read next buffer of data
				amt = read(fd, buff, BUFF_SIZE);
			}
			if(amt == -1) { //Error checking
				perror("read");
				handleClose(fd); //we need to clean up the fd
				printf("Err in read\n");
				continue;
			}
			newLines += fileNewLines;

			//print filename and count
			printf("Count: %u\tName: `%s`\n", fileNewLines, globuff.gl_pathv[i]);
			
			//close the file
			handleClose(fd);
		}

		printf("Total new lines: %u\n", newLines);

		globfree(&globuff);
		return 0;
	}

	//closes the file, handles associated errors with perror
	void handleClose(int fd) 
	{
		if(close(fd) != 0) //error checking
			perror("close");
	}

	void printHelp(char* prgmName)
	{
		printf("Usage: %s FILES...\n", prgmName);
		printf("Count the number of lines in specified FILES.\n");
	}

## 2.) Alias to easily ssh into RPi
`$ alias rpi='ssh blake.team2648.com'`

## 3.) Count directories on RPi
`$ cd /`     
`$ find . -type d | wc -l`

## 4.) gcc generate assembly and stop
`$ gcc mset.c -S`

## 5.) objdump an executeable with source intermixed
a.) `$ objdump -SlC mset > dump`    
b.) 7 assembly instructions in the main loop


## 6.) Custom program timer

	////////////////////////////////////////////////////////////////////////////////
	// ECE 331 - HW2
	// Author: Blake Bourque
	// Date: 1/31/2013
	// Purpose: function to read the RPi's free running timer.
	// @note: The timer increments once each microsecond.
	////////////////////////////////////////////////////////////////////////////////

	//sysconf():
	#include <unistd.h>
	//uint*:
	#include <stdint.h>
	//printf:
	#include <stdio.h>
	//mmap:
	#include <sys/mman.h>
	//open:
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	//errors:
	#include <errno.h>

	#include "time.hw2_6.h"

	// ***Forward declarations***

	//closes the file, handles associated errors with perror
	void handleClose(int fd);

	uint64_t getSystemTime() //returns -1 on error
	{
		static uint64_t* addy = NULL;

		if(addy != NULL)
			return *addy;

		int fd = open("/dev/mem", O_RDONLY);
		if(fd == -1) { //error checking
			perror("open");
			return -1; 
		}

		long pgsz = sysconf(_SC_PAGESIZE);					//Physical Page size
		if(pgsz == -1) {
			perror("sysconf");
			handleClose(fd);
			return -1;
		}

		void* v_ptr = mmap(NULL, pgsz, PROT_READ, MAP_SHARED, fd, 0x20003000);
		if(v_ptr == MAP_FAILED || v_ptr == NULL) {
			perror("mmap");
			handleClose(fd);
			return -1;
		}
		char* c_ptr = ((char*)v_ptr)+4; //mmap doesn't want to access the unaligned memory. Move ptr after mapping
		addy = (uint64_t*)c_ptr;
		handleClose(fd);
		return *addy;
	}

	//closes the file, handles associated errors with perror
	void handleClose(int fd) 
	{
		if(close(fd) != 0) //error checking
			perror("close");
	}

## 7.) Header for my getSystemTime function

	#ifndef __RPi_sys_time__
	#define __RPi_sys_time__

	// Get the system time, from the RPi's free running clock.
	// The value increments by 1 every microsecond.
	uint64_t getSystemTime();

	#endif

## 8.) Timing mset using code from #6

a.) Modified mset code:
	
	////////////////////////////////////////////////////////////////////////////////
	// ECE 331 - HW1
	// Author: Blake Bourque
	// Date: 1/24/2013
	// Purpose: Implement a function `mset` which mimics the behavior of c's `memset`
	// purely in c code. The below code uses two strategise to be faster than the 
	// sample code given:
	// 1. Where possible set 64bits (8 bytes) of memory at a time
	// 2. Pointers & Pointer arithmetic over indexing.
	// @note: code to measure time added.
	////////////////////////////////////////////////////////////////////////////////

	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <string.h>
	#include <stdint.h>

	#include "time.hw2_6.h"

	#define SIZE (128*1024*1024)

	////////////////////////////////////////////////////////////////////////////////
	// Forward Declarations
	////////////////////////////////////////////////////////////////////////////////
	void* mset(void *s, int c, size_t n);
	void check(void *s, int c, size_t n);

	////////////////////////////////////////////////////////////////////////////////
	// Main
	////////////////////////////////////////////////////////////////////////////////
	int main(int argc, char* argv[])
	{
		uint64_t start = getSystemTime();
		if(start == -1)
			return errno;

		char *m = (char *)malloc(SIZE);
		if (m==NULL) {
			perror("malloc");
			return errno; 
		}
		
		mset(m, 0x8, SIZE);
		//check(m, 0x8, SIZE); //uncomment this to check the output. (adds time)

		free(m);
		uint64_t fini = getSystemTime();
		if(fini == -1)
			return errno;
		printf("Time: %lld\n",(fini-start));
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////
	// Function to imitate c's memset function
	////////////////////////////////////////////////////////////////////////////////
	void* mset(void *s, int c, size_t n) 
	//s is a pointer to the first byte
	//c is the value of each byte
	//n is number of bytes
	{

		register uint64_t nVal = c;
		nVal |= (nVal << 8);
		nVal |= (nVal << 16);
		nVal |= (nVal << 32);

		register uintptr_t ptr = (uintptr_t)s;					
		register uintptr_t end = (uintptr_t)(ptr + n);	
		
		for (ptr; (ptr+8) < end; ptr+=8) {
			*((uint64_t *)(ptr)) = nVal;  //write 8 bytes
		}

		if( n % 8 != 0) {		//do the last few bytes individually 
			ptr -= 8; 				//Clear out the increment from the last loop check
			for (ptr; ptr<end; ptr++) {                  
				*((unsigned char *)ptr)=(unsigned char)c;
			}
		}

		return s;
	}
	////////////////////////////////////////////////////////////////////////////////
	// Function to ensure that the output is correct
	////////////////////////////////////////////////////////////////////////////////
	void check(void *s, int c, size_t n)
	{
		register int numERR =0;

		register uintptr_t ptr = (uintptr_t)s;
		register uintptr_t end = (uintptr_t)(ptr + n);

		for (ptr; ptr < end; ptr++) {
			if(*((unsigned char *)ptr)!=(unsigned char)c){
				numERR ++;
				printf("ERR @ Addy: %p\n", (void*)ptr);
			}
		}
		printf("Error: %d\n", numERR);
	}


b.) Compile & Link getSystemTime library    
In my makefile:

	mset: mset.hw2_5.o time.hw2_6.o
		${CC} -g -o $@ $^ 

or(as done by make):  
`$ cc -std=gnu99   -c -o mset.hw2_5.o mset.hw2_5.c`  
`$ cc -std=gnu99   -c -o time.hw2_6.o time.hw2_6.c`  
`$ cc -g -o mset mset.hw2_5.o time.hw2_6.o`

or (using gcc):  
`$ gcc -c -o mset.hw2_5.o mset.hw2_5.c`  
`$ gcc -c -o time.hw2_6.o time.hw2_6.c`  
`$ gcc -o mset mset.hw2_5.o time.hw2_6.o`

c.) System timer counts: `433,221`

d.) The times do not agree. Possible reasons they don't match:
1. My getSystemTime function has the overhead of closing, then opening `/dev/mem` inside the period being timed.
2. the time function used previously runs as part of the shell, which indicates that setup and teardown of the mset program is included in the time. Conversely, my getSystemTime function only counts the time between the calling of main, and the end of freeing memory.

Even though the values reported aren't identical 0.433221s(getSystemTime) and 0.437s(time) the are very close, I would argue close enough.