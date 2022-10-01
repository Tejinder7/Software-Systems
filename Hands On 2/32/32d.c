//Name: Tejinder Singh
//Registration number: MT2022124

//32. Write a program to implement semaphore to protect any critical section.
//d. remove the created semaphore

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

	printf("Enter the semaphore id to be deleted\n");
	scanf("%d", &semid);

	semctl(semid, 0, IPC_RMID);
	printf("Semaphore removed\n");
}
