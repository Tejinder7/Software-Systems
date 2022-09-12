//Name: Tejinder Singh 
//Registration Number: MT2022124

//6. Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int i; char buff[100];
	i= read(0, buff, sizeof(buff));
	write(1, buff, i);	
}
