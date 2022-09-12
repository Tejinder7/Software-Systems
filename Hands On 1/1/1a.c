//Name: Tejinder Singh 
//Registration Number: MT2022124

//1. Create the following types of a files using system call a). soft link (symlink system call)

#include <unistd.h>
#include <stdio.h>

int main(void){
	symlink("file1", "sftlnk");
	perror("link ret: ");
}
