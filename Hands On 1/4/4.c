//Name: Tejinder Singh 
//Registration Number: MT2022124

//4. Write a program to open an existing file with read write mode. Try O_EXCL flag also.

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void){
	int fd1, fd2;
	fd1= open("hello.c", O_RDWR|O_CREAT|O_EXCL, 0744);
	fd2= open("hello.c", O_RDWR);
	printf("fd1: %d\nfd2: %d\n", fd1, fd2);
}

