//Name: Tejinder Singh
//Registration Number: MT2022124

//16. Write a program to send and receive data from parent to child vice versa. Use two way communication.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	int fd1[2], fd2[2];
	int childPid;
	char buff[128];
	pipe(fd1);
	pipe(fd2);

	printf("\t Executing two way communication\n");

	childPid= fork();
	if(childPid== -1){
		perror("Fork Error\n");
	}
	else{

		if(childPid== 0){
			
			close(fd1[1]);
			close(fd2[0]);
		
			read(fd1[0], &buff, 29);
			printf("Reading from Parent...\n");
			printf("%s", buff);
		
			write(fd2[1], "Hello from child\n", 17);
		}

		else{
			close(fd1[0]);
			close(fd2[1]);

			write(fd1[1], "Hello from parent\n", 18);
		
			read(fd2[0], &buff, 29);
			printf("Reading from child...\n");
		
			printf("%s", buff);
		}
	}

}

