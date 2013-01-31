////////////////////////////////////////////////////////////////////////////////
// ECE 331 - HW1
// Author: Blake Bourque
// Date: 1/24/2013
// Purpose: Implement a function `mset` which mimics the behavior of c's `memset`
// purely in c code. The below code uses two strategise to be faster than the 
// sample code given:
// 1. Where possible set 64bits (8 bytes) of memory at a time
// 2. Pointers & Pointer arithmetic over indexing.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

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
	char *m = (char *)malloc(SIZE);
	if (m==NULL) {
		perror("malloc");
		return errno; 
	}
	
	mset(m+1, 0x8, SIZE-1);
	check(m, 0x8, SIZE); //uncomment this to check the output. (adds time)

	free(m);
	return(0);
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
