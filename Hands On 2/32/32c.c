//Name: Tejinder Singh
//Registration number: MT2022124

//32. Write a program to implement semaphore to protect any critical section.
//c. protect multiple pseudo resources ( may be two) using counting semaphore

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <unistd.h>    
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void){
	key_t key;
	int semid;
	int fd;
	int status;
	char buff[128];

	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
	} sem;

	key= ftok(".", 'c');
	semid= semget(key, 1, 0);
	if(semid== -1){
		semid= semget(key, 1, IPC_CREAT| 0744);

		sem.val= 2;
		semctl(semid, 0, SETVAL, sem);
	}

        fd= open("pseudo_resource.txt", O_RDWR| O_CREAT, 0744);


	struct sembuf semOp;
        semOp.sem_num= 0;
        semOp.sem_flg= IPC_NOWAIT;

        printf("Entering Critical Section\n");
        semOp.sem_op= -1;
        status= semop(semid, &semOp, 1);

        if(status== -2){
                printf("Error while acquiring lock\n");
		exit(-1);
        }
        printf("Inside critical section\n");
        read(fd, &buff, sizeof(buff));
     
        printf("Data in file: %s\n", buff);

        printf("Press any key to exit critical section\n");
        getchar();

	semOp.sem_op= 1;
        status= semop(semid, &semOp, 1);
        if(status== -1){
                printf("Error while operating on semaphore\n");
                exit(-1);
        }
        close(fd);
}
