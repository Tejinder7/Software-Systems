//Name: Tejinder Singh 
//Registration Number: MT2022124

//11. Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
//c.) use fcntl

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
	int fd1, fd2, fd3;
	char buff[128];
	
	fd1= open("file5_2", O_RDWR);

	printf("Duplicating file descriptor using fcntl\n");
	fd2= fcntl(fd1, F_DUPFD);
	
	printf("Writing using file descriptor 1\n");
	write(fd1, "This was ", 9);

	printf("Writing using copied file descriptor\n");
	write(fd2, "duplicated by fcntl\n",20);
        
	fd3= open("file5_2", O_RDONLY);
	read(fd3, buff, sizeof(buff));
	printf("Output: %s\n", buff);

	
	close(fd1);
	close(fd2);       

}
