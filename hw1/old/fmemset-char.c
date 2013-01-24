// A. Sheaff 1/17/2013
// Code to make memset and test
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Buffer size
#define SIZE (128*1024*1024)

void * mset(void *s, int c, size_t n);

int main(int argc, char * argv[])
{
	int i,j;
	// Allocate memory
	char *m=(char *)malloc(SIZE);
	if (m==NULL) {	// Check for errors
		perror("malloc");
		return errno;
	}
	// Set memory
	mset(m,0,SIZE);
	// Free
	free(m);
	
	return 0;
}

// Set a memory buffer to a given value
void * mset(void *s, int c, size_t n)
{
	register size_t i;

	// For every memory location set the value
	for (i=0;i<n;i++) {
		((unsigned char *)s)[i]=(unsigned char)c;
	}
	return s;
}
