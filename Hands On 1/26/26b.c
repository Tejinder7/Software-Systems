//Name: Tejinder Singh 
//Registration Number: MT2022124

//26. Write a program to execute an executable program.
//b.) passe some input to an executable program

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	printf("This program will execute the executable program by passing an input\n");
	char *argv[]= {"null", "executable2", NULL};
	execv("./executable2",  argv);
	perror("status:");
}
