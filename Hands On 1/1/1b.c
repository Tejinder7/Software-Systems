//Name: Tejinder Singh 
//Registration Number: MT2022124

//1. Create the following types of a files using system call b). hard link (link system call)

#include <unistd.h>
#include <stdlib.h>

int main(void){

	link("file1", "hrdlnk");
	perror("link return: ");

}
