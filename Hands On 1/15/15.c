//Name: Tejinder Singh 
//Registration Number: MT2022124

//15. Write a program to display the environmental variable of the user (use environ).

#include <unistd.h>
#include <stdio.h>

int main(void){
	extern char **environ;
	int i= 0;

	printf("Following is the list of the environment variables\n");

	while(environ[i]){
		printf("%s\n", environ[i++]);
	}

}
