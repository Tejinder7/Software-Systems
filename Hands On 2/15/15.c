//Name: Tejinder Singh 
//Registration Number: MT2022124

//15. Write a simple program to send some data from parent to the child process.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
	int fd[2];
	int childPid;
	char buff[128];

	pipe(fd);
	childPid= fork();
	if(childPid== -1){
		perror("Fork Error\n");
	}
	else{
		if(childPid== 0){
			
			close(fd[1]);

			read(fd[0], &buff, sizeof(buff));
			printf("Child is reading from the pipe\n");
			printf("Data from parent: \n");
			printf("%s\n", buff);
		}
		else{
			close(fd[0]);

			printf("Type a message to write into the pipe\n");
			scanf("%[^\n]", buff);

			printf("Parent is writing into the pipe...\n");
			write(fd[1], &buff, sizeof(buff));
			wait(0);
		}
	}
}
