//Name: Tejinder Singh
//Registration Number: MT2022124

//17. Write a program to execute ls -l | wc.
//a.) use fcntl

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void){
	int fd[2];
	int childPid;

	pipe(fd);
	childPid= fork();

	if(childPid== -1){
		perror("Fork Error\n");
	}

	else{

		if(childPid== 0){
			close(fd[0]);
			close(1);
			fcntl(fd[1], F_DUPFD, 1);
			execl("/bin/ls", "ls", "-l", NULL);
		}
		else{
			close(fd[1]);
			close(0);
			fcntl(fd[0], F_DUPFD, 0);
			printf("The word count of the current directory is\n");
			execl("/usr/bin/wc", "wc", "-l", NULL);
		}
	}
}
