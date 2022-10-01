#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fifo2_status, fifo3_status;

	fifo2_status= mknod("./fifo2", S_IFIFO| 0744, 0);
	
	if(fifo2_status== -1)
		printf("Error while creating fifo2\n");
	else
		printf("Creation successful\n");

	fifo3_status= mknod("./fifo3", S_IFIFO| 0744, 0);

	if(fifo3_status== -1)
		printf("Error while creating fifo3\n");
	else
		printf("Creation successful\n");
}
