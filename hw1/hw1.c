#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
int main(void) 
{
	long pages = sysconf(_SC_PHYS_PAGES);		//Physical Pages
	long pgsz = sysconf(_SC_PAGESIZE);			//Physical Page size
	long proc = sysconf(_SC_NPROCESSORS_ONLN);	//Online Processors
	
	printf("Pages: %ld \n", pages); 
	printf("Page Size: %ld \n", pgsz); 
	printf("Processors: %ld \n", proc); 		//Online Processors

	struct utsname my_uname;
	if(uname(&my_uname) == -1)
	   printf("uname call failed!");
	else
	   printf("Machine:%s\n", my_uname.machine);

}

