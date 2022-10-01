//Name: Tejinder Singh
//Registration number: MT2022124

//30. Write a program to create a shared memory.
//a. write some data to the shared memory
//b. attach with O_RDONLY and check whether you are able to overwrite.
//c. detach the shared memory
//d. remove the shared memory

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/shm.h>   
#include <unistd.h>    
#include <stdio.h>
#include <stdlib.h>

int main(void){
	key_t key;
	int shmid;
	//a.) Writing data into shared memory
	char *data;

	key= ftok(".", 'a');

	shmid= shmget(key, 1024, IPC_CREAT| 0744);
	data= shmat(shmid, 0, 0);

	printf("Enter text to write into the shared memory\n");
	scanf("%[^\n]", data);

	//b.) attach with O_RDONLY and check whether you are able to overwrite.
	char *rdonly_data;

	rdonly_data= shmat(shmid, 0, SHM_RDONLY);
	//printf("Enter text to write into the shared memory\n");
	//The following line will result in a segmentation fault because the pointer is read only
	//scanf("%[^\n]", rdonly_data);
	
	//c.)detach the shared memory
	char response;
	printf("Do you want to detach the shared memory: (y/n)\n");
	scanf(" %c", &response);

	if(response== 'y'){
		printf("Detaching shared memory\n");
		shmdt(data);
		shmdt(rdonly_data);
	}
	else
		printf("Moving ahead..\n");

	//d.)remove the shared memory
	printf("Do you want to remove the shared memory: (y/n)\n");
        scanf(" %c", &response);

        if(response== 'y'){
                printf("Removing shared memory\n");
                shmctl(shmid, IPC_RMID, NULL);
		printf("Removed shared memory");
        }
        else{
                printf("Exiting program\n");
		exit(0);
	}
}
