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
	fd1= open("fifo2", O_RDONLY);
	
	fd2= open("fifo3", O_WRONLY);

	printf("\nReading from fifo2\n");
	read(fd1, buff1, sizeof(buff1));

	printf("Text from fifo2 is:\n%s\n\n", buff1);

	printf("Enter text to write into fifo3:\n");
        scanf("%[^\n]", buff2);
        write(fd2, buff2, sizeof(buff2));

}
