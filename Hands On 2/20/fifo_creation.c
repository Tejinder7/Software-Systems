#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fifo1_status;

	fifo1_status= mknod("./fifo1", S_IFIFO| 0744, 0);
	
	if(fifo1_status== -1)
		printf("Error while creating fifo2\n");
	else
		printf("Creation successful\n");
}
