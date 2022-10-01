//Name: Tejinder Singh
//Registration number: MT2022124

//32. Write a program to implement semaphore to protect any critical section.
//b. protect shared memory from concurrent write access

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <unistd.h>    
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(void){
	key_t key;
	int semid;

	key_t shmkey;
	int shmid;
	char *data;
	int status;

	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
	} sem;

	key= ftok(".", 'a');
	semid= semget(key, 1, 0);
	if(semid== -1){
		semid= semget(key, 1, IPC_CREAT| 0744);

		sem.val= 1;
		semctl(semid, 0, SETVAL, sem);
	}

	shmkey= ftok(".", 's');
	shmid= shmget(shmkey, 1024, IPC_CREAT| 0744);
	data= shmat(shmid, 0, 0);

	struct sembuf semOp;
	semOp.sem_num= 0;
	semOp.sem_flg= 0;

	printf("Entering critical section\n");

	semOp.sem_op= -1;
	status= semop(semid, &semOp, 1);

	if(status== -1){
		printf("Error while operating on semaphore\n");
		exit(-1);
	}

	printf("Inside critical section\n");

	printf("Writing into shared memory\n");
	printf("Enter text to write into shared memory\n");

	scanf("%[^\n]", data);

	printf("Reading content from shared memory\n");
	printf("%s\n", data);

	printf("Press any key to exit critical section\n");
	getchar();

	semOp.sem_op= 1;
	semop(semid, &semOp, 1);

	printf("Exiting critical section\n");
}
