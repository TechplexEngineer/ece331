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