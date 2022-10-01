//Name: Tejinder Singh
//Registration number: MT2022124

//23. Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
	int fifo_status;
	long maxFileNum, pipeSize;

	fifo_status= mknod("./fifo5", S_IFIFO| 0774, 0);

	maxFileNum= sysconf(_SC_OPEN_MAX);
	printf("Maximum number of files that can be opened within a process are: %ld\n", maxFileNum);
	pipeSize= pathconf("./fifo5", _PC_PIPE_BUF);
	printf("Size of pipe(Circular Buffer): %ld\n", pipeSize);
}

