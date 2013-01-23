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
{
	register size_t i;
	register uint64_t new = c; //why is c not a byte?
	new |= (new << 8);
	new |= (new << 16);
	new |= (new << 32);
	
	for(i=0; i<(n/8); i++) {
		((uint64_t*)s)[i] = new;
	}
	return s;
}



