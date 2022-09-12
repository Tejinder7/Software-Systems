//Name: Tejinder Singh 
//Registration Number: MT2022124


//3. Write a program to create a file and print the file descriptor value. Use creat ( ) system call.

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
	int fd;
	fd= creat("file2", 0744);
	printf("File Descriptor value is: %d \n", fd);

}
