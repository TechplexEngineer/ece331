////////////////////////////////////////////////////////////////////////////////
// ECE 331 - HW1
// Author: Blake Bourque
// Date: 1/24/2013
// Purpose: a small program to print some information about our RPi
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
int main(void) 
{
	long pages = sysconf(_SC_PHYS_PAGES);				//Physical Pages
	long pgsz = sysconf(_SC_PAGESIZE);					//Physical Page size
	long proc = sysconf(_SC_NPROCESSORS_ONLN);	//Online Processors
	
	printf("Pages: %ld \n", pages); 
	printf("Page Size: %ld \n", pgsz); 
	printf("Processors: %ld \n", proc); 				

	struct utsname my_uname;
	if(uname(&my_uname) == -1)
		printf("uname call failed!");
	else
		printf("Machine:%s\n", my_uname.machine);//machine/hardware identifier 
}

