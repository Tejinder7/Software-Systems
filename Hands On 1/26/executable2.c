//Program to be executed from another program by passing some arguements

#include <stdio.h>
#include <string.h>

int main(int args, char *arg[]){
	printf("The name of the program is %s\n", arg[1]);
}

