//Name: Tejinder Singh 
//Registration Number: MT2022124

//24. Write a program to create an orphan process.

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	if(!fork()){
		printf("Before becoming orphan, parent process id is: %d\n", getppid());
		printf("Putting child to sleep \n");
		sleep(3);
		printf("Child process is awake and orphan\n");
		printf("After becoming orphan, parent process id is: %d\n", getppid());
		exit(0);
	}
	else{
		sleep(1);
		printf("Parent process id: %d\n", getpid());
		printf("Exiting parent process \n");
		exit(0);
	}

}
