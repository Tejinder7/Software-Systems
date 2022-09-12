//Name: Tejinder Singh 
//Registration Number: MT2022124

//27. Write a program to execute ls -Rl by the following system calls
//c.) execle

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

extern char* environ;

int main(void){
	char dir[100];
	printf("Enter name of the directory\n");
	scanf("%s", dir);

	execle("/bin/ls", "ls", "-Rl", dir, NULL, environ);
}
