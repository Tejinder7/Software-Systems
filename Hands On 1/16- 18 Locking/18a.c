//Name: Tejinder Singh 
//Registration Number: MT2022124

//18. Write a program to perform Record locking.
//a. Implement write lock
//b. Implement read lock
//Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

struct {
                int train_num;
                int ticket_count;
        }db;

int main(void){
	int fd, num;
	
	fd= open("records.txt", O_RDWR);
	printf("Select train number from 1 to 3\n");
	scanf("%d", &num);

	struct flock lock;
	lock.l_type= F_WRLCK;
	lock.l_whence= SEEK_SET;
	lock.l_start= (num-1)*sizeof(db);
	lock.l_len= sizeof(db);
	lock.l_pid= getpid();

	printf("Reading value of ticket count of train number %d\n", num);
	lseek(fd, (num-1)*sizeof(db),  SEEK_SET);
	
	printf("Entering Critical Section\n");
	fcntl(fd, F_SETLKW, &lock);
	
	read(fd, &db, sizeof(db));

	printf("Current ticket count: %d\n", db.ticket_count);
	db.ticket_count++;
	
	lseek(fd, -1* sizeof(db), SEEK_CUR);
	write(fd, &db, sizeof(db));
	
	printf("Press any key to exit critical section\n");
	getchar();
	getchar();
	
	printf("Exiting critical section\n");
	lock.l_type= F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
}
