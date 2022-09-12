//Name: Tejinder Singh 
//Registration Number: MT2022124

//8. Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;
	char buff;
	fd= open("source", O_RDONLY);

	while(read(fd, &buff, 1)!=0){
		if(buff== '\n'){
			printf("\n");
		}
		else{
			printf("%c", buff);
		}
	}
}
