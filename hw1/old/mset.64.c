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
		return errno;
	}
	
	mset(m, 0, SIZE);

	free(m);
	return(0);
}


void* mset(void *s, int c, size_t n)
{
	register size_t i;
	for(i=0; i<n; i+=64) {
		((uint64_t*)s)[i] = (uint64_t)c;
	}
	return s;
}



