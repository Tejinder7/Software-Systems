//Name: Tejinder Singh
//Registration Number: MT2022124

//14. Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.

#include <unistd.h>
#include <stdio.h>

int main(void){
	int fd[2];
	char buff[128];
	pipe(fd);

	printf("Type a message to write into the pipe\n");
	scanf("%[^\n]", buff);

	printf("Writng into the pipe...\n");
	write(fd[1], &buff, sizeof(buff));

	printf("Reading from the pipe...\n");
	read(fd[0], &buff, sizeof(buff));
	printf("%s \n", buff);
	getchar();

}
