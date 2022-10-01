#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fifo4_status;

	fifo4_status= mknod("./fifo4", S_IFIFO| 0744, 0);
	
	if(fifo4_status== -1)
		printf("Error while creating fifo4\n");
	else
		printf("Creation successful\n");
}
