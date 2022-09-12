//Name: Tejinder Singh 
//Registration Number: MT2022124

//11. Write a program to open a file, duplicate the file descriptor and append the file with both thedescriptors and check whether the file is updated properly or not.
//a). use dup

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd1, fd2, fd3;
	char buff[128];
	fd1= open("file5", O_WRONLY);

	printf("Duplicating file using dup\n");
	fd2= dup(fd1);
	
	printf("Writing into the file using descriptor fd1\n");
	write(fd1, "Hi ", 3);
	
	printf("Writing into the file using descriptor fd2\n");
	write(fd2, "I am duplicate\n", 15);

	close(fd1);
	close(fd2);

	fd3= open("file5", O_RDONLY);
	read(fd3, buff, sizeof(buff));
	printf("Output: %s\n", buff);

}
