//Name: Tejinder Singh
//Registration number: MT2022124

//32. Write a program to implement semaphore to protect any critical section.
//a. rewrite the ticket number creation program using semaphore

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

	int fd;
        int status;
        //Creating structure to manipulate the file data
        struct db{
                int ticket_no;
        }db1;

        fd= open("db", O_RDWR);
	struct sembuf semOp;
        semOp.sem_num= 0;
        semOp.sem_flg= 0;

        printf("Entering Critical Section\n");
        semOp.sem_op= -1;
        status= semop(semid, &semOp, 1);

        if(status== -1){
                printf("Error while acquiring lock\n");
                close(fd);
        }
        printf("Inside critical section\n");
        read(fd, &db1, sizeof(struct db));
        printf("Previous value of ticket number: %d\n", db1.ticket_no);
        db1.ticket_no++;
        printf("Current value of ticket number: %d\n", db1.ticket_no);

	lseek(fd, 0, SEEK_SET);

        //Writing the updated value into the file
        write(fd, &db1, sizeof(struct db));
	perror("write");

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
