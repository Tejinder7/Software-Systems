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
	int fd;
	int result;
	char buff[128];

	struct timeval tv;
	fd_set rfds;

	fd= open("fifo4", O_RDONLY);

	tv.tv_sec= 10;
	tv.tv_usec= 0;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	printf("Reading from FIFO\n");

	result= select(fd+ 1, &rfds, NULL, NULL, &tv);

	if(result){
		printf("Data is available\n");
		read(fd, buff, sizeof(buff));
		printf("Data is: %s\n", buff);
	}
	else{
		printf("Data is not avaiable from FIFO\nMoving ahead...\n");
	}
}
