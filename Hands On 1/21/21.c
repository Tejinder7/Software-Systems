//Name: Tejinder Singh 
//Registration Number: MT2022124

//21. Write a program, call fork and print the parent and child process id.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	if(fork()==0){
		printf("Child process id is: %d\n", getpid());
		printf("Parent process id fetched from child process: %d\n", getppid());
	}
	else{
		sleep(1);
		printf("Parent proces id is: %d\n", getpid());
	}

}
