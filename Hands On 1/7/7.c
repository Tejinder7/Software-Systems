//Name: Tejinder Singh 
//Registration Number: MT2022124

//7. Write a program to copy file1 into file2 ($cp file1 file2).

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void){
	int fd1, fd2, i; char  buff[512];
	fd1= open("source.txt", O_RDONLY);
	printf("Opening source file and reading its content\n");
	
	i= read(fd1, buff, sizeof(buff));
	printf("Writing the content to destination file\n");
	
	fd2= open("destination.txt", O_WRONLY);
	write(fd2, buff, i);
	
	printf("File Copied\n");
	
	close(fd1);
	close(fd2);

}

