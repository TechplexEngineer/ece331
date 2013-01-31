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

#ifdef __debug_time
int main(int argc, char* argv[])
{
	uint64_t value = getSystemTime();
	if(value == -1)
		return errno;
	printf("Time (us): %llx\n", value);
	for(int i=500000; i>0; i--);
	printf("Time (us): %llx\n", value);
}
#endif

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