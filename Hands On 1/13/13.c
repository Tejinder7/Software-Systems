//Name: Tejinder Singh 
//Registration Number: MT2022124

//13. Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>

int main(void){
	int value = 0;
    	struct timeval time;
    	fd_set fds;

    	FD_ZERO(&fds);// clears all file descriptors from set
    	FD_SET(0, &fds);
    	time.tv_sec = 10;
    	time.tv_usec = 0;
	
	value= select(1, &fds, NULL, NULL, &time);

	if(value== -1){
		perror("Error: ");
	}
	else if(value== 0){
		printf("No data was entered within the 10 second timeframe\n");
	}
	else{
		printf("Data entered\n");
	}

}
