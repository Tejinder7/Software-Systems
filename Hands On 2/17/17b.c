//Name: Tejinder Singh
//Registration Number: MT2022124

//17. Write a program to execute ls -l | wc.
//b.) use dup2

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	int fd[2];
	int childPid;

	pipe(fd);
	childPid= fork();
	
	if(childPid== -1){
		perror("Fork error\n");
	}

	else{

		if(childPid== 0){
			close(fd[0]);
			dup2(fd[1], 1);
			execl("/bin/ls", "ls", "-l", NULL);
		}
		else{
			close(fd[1]);
			dup2(fd[0], 0);
			printf("The word count of the current directory is\n");
			execl("/usr/bin/wc", "wc", "-l", NULL);
		}
	}
}
