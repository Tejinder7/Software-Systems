//Name: Tejinder Singh 
//Registration Number: MT2022124

/*10. Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data.
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd, seek;
	fd= open("file4", O_WRONLY);
	
	printf("Writing into the file\n");
	write(fd, "Hello, I am Hands On\n", 21);
	
	printf("Moving the file pointer by 10 bytes\n");
	seek= lseek(fd, 10L, SEEK_CUR);
	
	printf("The return value of lseek is: %d\n", seek);
	write(fd, "Complete all questions\n", 24);
	
	close(fd);

}
