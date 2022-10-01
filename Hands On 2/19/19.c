//Name: Tejinder Singh
//Registration number: MT2022124

//19. Create a FIFO file by
//a.) mknod command
//b.) mkfifo command
//c.) use strace command to find out, which command (mknod or mkfifo) is better.
//c.) mknod system call
//d.) mkfifo library function

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
	int status_mkfifo;
	int status_mknod;

	//Creatig fifo special file using mkfifo
	status_mkfifo= mkfifo("./mkfifo", 0744);

	if(status_mkfifo== -1){
		printf("Error creating FIFO file\n");
	}
	else{
		printf("Creation of FIFO file successful\n");
	}

	//Creating fifo special file using mknod
	
	status_mknod= mknod("./mknod", S_IFIFO| 0774, 0);
	
	if(status_mknod== -1){
		printf("Error creating FIFO file\n");
	}
	else{
		printf("Creation of FIFO file successful\n");
	}

}

//mkfifo actually calls mknod() and this mkfifo() is just doing some extra steps on top of mknod() because mkfifo() is a library function whereas mknod() is the actual system call. Therefore, mknod() is always going to be faster than mkfifo().
