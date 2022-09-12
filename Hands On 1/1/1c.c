//Name: Tejinder Singh 
//Registration Number: MT2022124

//1. Create the following types of a files using system call c.) FIFO (mkfifo Library Function or mknod system call)

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void){
	mknod("Myfifo", S_IFIFO, 0);
	perror("Creation: ");

}
