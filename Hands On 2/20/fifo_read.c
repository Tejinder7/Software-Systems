//Name: Tejinder Singh
//Registration number: MT2022124

//20. Write two programs so that both can communicate by FIFO -Use one way communication.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	char buff[128];
	int fd;
	printf("Reading from FIFO file\n");

	fd= open("fifo1", O_RDONLY);
	read(fd, buff, sizeof(buff));
	printf("The text from FIFO file is:\n%s\n", buff);
}
