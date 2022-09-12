//Name: Tejinder Singh 
//Registration Number: MT2022124

//23. Write a program to create a Zombie state of the running program.

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
	if(!fork()){
		printf("Child process id is: %d\n", getpid());
		printf("Child process sleeping\n");
		sleep(5);
		printf("Child process wakes up\n");
		printf("Exiting Child process\n");
		printf("Child is in zombie state because parent is sleeping\n");
		exit(0);
	}
	else{
		sleep(2);
		printf("Parent process id is: %d\n", getpid());
		printf("Parent process sleeping\n");
		sleep(20);
	}
}
