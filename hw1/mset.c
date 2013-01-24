#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#define SIZE (128*1024*1024)

void* mset(void *s, int c, size_t n);

int main(int argc, char* argv[])
{
	char *m = (char *)malloc(SIZE);
	if (m==NULL) {
		perror("malloc");
		return errno; //global...?
	}
	
	mset(m, 0, SIZE);

	free(m);
	return(0);
}


void* mset(void *s, int c, size_t n) 
//s is a pointer to the first byte
//c is the value of each byte
//n is number of bytes
{
	//register size_t i;
	uintptr_t
	register uint64_t* place_8 = (uint64_t*)s;
	register uint64_t new = c; //why is c not a byte?
	new |= (new << 8);
	new |= (new << 16);
	new |= (new << 32);

	for(place_8; place_8 < place_8+(n/8); place_8++) {
		*place_8 = new;
	}
	if(n%8 != 0) {
		place_8++;//get to the end of the 8 bytes that are set
		register uint8_t* place_1 = (uint8_t*)place_8;
		for(int i=0; i<n%8; i++)
	}
	
	// for(i=0; i<(n/8); i++) {
	// 	((uint64_t*)s)[i] = new;
	// }
	return s;
}



