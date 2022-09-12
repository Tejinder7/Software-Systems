//Name: Tejinder Singh 
//Registration Number: MT2022124

//22. Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;
	char buff1[128]= "This is written by parent\n";
	char buff2[128]= "This is written by child\n";
	
	fd= open("temp.txt", O_RDWR| O_CREAT, 0744);
	
	if(!fork()){
		write(fd, &buff2, sizeof(buff2));
	}	
	else{
		write(fd, &buff1, sizeof(buff1));
	}

	close(fd);

}
