//Name: Tejinder Singh
//Registration number: MT2022124

//21. Write two programs so that both can communicate by FIFO -Use two way communications.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void){
	int fd1, fd2;
	char buff1[128];
	char buff2[128];
	fd1= open("fifo2", O_WRONLY);
	fd2= open("fifo3", O_RDONLY);

	printf("Enter text to write into fifo2:\n");
	scanf("%[^\n]", buff1);
	write(fd1, buff1, sizeof(buff1));

	printf("\nReading from fifo3\n");
	read(fd2, buff2, sizeof(buff2));
	printf("Text from fifo3 is:\n%s\n", buff2);
}
