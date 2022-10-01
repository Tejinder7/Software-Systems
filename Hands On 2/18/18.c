//Name: Tejinder Singh
//Registration number: MT2022124

//18. Write a program to find out total number of directories on the pwd. Execute ls -l | grep ^d | wc ? Use only dup2.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	int fd1[2], fd2[2];
	int child_1, child_2;

	pipe(fd1);
	pipe(fd2);

	child_1= fork();

	if(child_1== -1){
		perror("Child 1 fork error\n");
	}

	else{
		if(child_1== 0){
			close(fd1[0]); //closing read of pipe1
			close(fd2[0]);
			close(fd2[1]); //closing both ends of pipe2
			
			dup2(fd1[1], 1);
			execl("/usr/bin/ls", "ls", "-l", NULL);
		}
		else{
			child_2= fork();
			
			if(child_2== -1){
				perror("Child 2 fork error\n");
			}
			
			else{
				if(child_2== 0){
					close(fd1[1]); //Closing write of pipe1
					close(fd2[0]); //Closing read of pipe2

					dup2(fd1[0], 0);
					dup2(fd2[1], 1);
					execl("/usr/bin/grep", "grep", "^d", NULL);
				}
				else{
					close(fd1[0]);
					close(fd1[1]);
					close(fd2[1]);

					dup2(fd2[0], 0);
					
					printf("The number of directories in pwd are:\n");
					execl("/usr/bin/wc", "wc", "-l", NULL);
				}
			}
		}
	}

}
