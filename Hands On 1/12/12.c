//Name: Tejinder Singh 
//Registration Number: MT2022124

//12. Write a program to find out the opening mode of a file. Use fcntl.

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
	int fd, status, mode;
	fd= open("file6", O_RDWR| O_CREAT, 0744);
	status= fcntl(fd, F_GETFL);
	mode= status & O_ACCMODE;

	if(mode== O_RDWR){
		printf("File is opened in read/write mode\n");
	}
	else if(mode== O_RDONLY){
                printf("File is opened in read mode\n");
        }
	else if(mode== O_WRONLY){
                printf("File is opened in write mode\n");
        }
	close(fd);

}
