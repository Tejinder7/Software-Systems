//Name: Tejinder Singh
//Registration number: MT2022124

//31. Write a program to create a semaphore and initialize value to the semaphore.
//a. create a binary semaphore
//b. create a counting semaphore

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <unistd.h>    
#include <stdio.h>  

int main(void){
	key_t key;
	int semid;

	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short int *array
	} sem;

	key= ftok(".", 'a');
	semid= semget(key, 1, IPC_CREAT| 0774);

	printf("Creating and initializing a binary semaphore\n");

	sem.val= 1; //Binary semaphore
	semctl(semid, 0, SETVAL, sem);
	printf("Creation successful\n");
}
