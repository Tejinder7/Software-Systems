//Name: Tejinder Singh 
//Registration Number: MT2022124

//27. Write a program to execute ls -Rl by the following system calls
//d.) execv

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	char dir[100];
	printf("Enter name of the directory\n");
	scanf("%s", dir);
	char *args[]= {"/bin/ls", "-Rl", dir, NULL};

	execv(args[0], args);
}
