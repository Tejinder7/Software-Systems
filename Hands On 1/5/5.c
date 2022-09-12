//Name: Tejinder Singh 
//Registration Number: MT2022124

//5. Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.

#include<stdio.h>
#include<fcntl.h>

int main(void){
	int fd1, fd2, fd3, fd4, fd5;
	printf("Creating five new files\n");
	fd1= open("file1", O_RDWR|O_CREAT, 0744);
       	fd2= open("file2", O_RDWR|O_CREAT, 0744);
        fd3= open("file3", O_RDWR|O_CREAT, 0744);
        fd4= open("file4", O_RDWR|O_CREAT, 0744);
        fd5= open("file5", O_RDWR|O_CREAT, 0744);
	for(;;);
	
}
