//Name: Tejinder Singh 
//Registration Number: MT2022124

//26. Write a program to execute an executable program.
//a.) use some executable program

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	printf("This program will execute executable program\n");
	char *args[]= {NULL};
	execv("./executable", args);
}

