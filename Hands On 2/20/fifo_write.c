//Name: Tejinder Singh
//Registration number: MT2022124

//20. Write two programs so that both can communicate by FIFO -Use one way communication.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	char buff[128];
	int fd;
	//Program to write into the FIFO file

	fd= open("fifo1", O_WRONLY);
	printf("Write something into the FIFO file:\n");
	scanf("%[^\n]", buff);
	
	write(fd, buff, sizeof(buff));

}
