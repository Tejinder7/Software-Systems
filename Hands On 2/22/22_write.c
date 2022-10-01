//Name: Tejinder Singh
//Registration number: MT2022124

//22. Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.

#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>     
#include <sys/time.h>  
#include <unistd.h>    
#include <stdio.h>  

int main(void){
	char buff[128];
	int fd;
	fd= open("fifo4", O_WRONLY);
	perror("fd");

	printf("Write into the FIFO file \n");
	scanf("%[^\n]", buff);

	write(fd, buff, sizeof(buff));
}
