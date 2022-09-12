//Name: Tejinder Singh 
//Registration Number: MT2022124

//11. Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
//b.) use dup2

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd1, fd2;
	fd1= open("file5", O_WRONLY);
	int i= dup2(fd1, fd2);
	
	printf("%d", i);
	printf("fd1: %d, fd2: %d ", fd1, fd2);
	write(fd1, "Hi ", 3);
	write(fd2, "I am another duplicate\n", 22);
	
}

