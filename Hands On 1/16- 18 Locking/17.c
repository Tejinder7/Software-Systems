//Name: Tejinder Singh 
//Registration Number: MT2022124

/* 17. Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file. */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;
	struct db{
		int ticket_no;
	}db2;
	struct flock lock;
	fd= open("db", O_RDWR);
	lock.l_type= F_WRLCK;
	lock.l_whence= SEEK_SET;
	lock.l_start= 0;
	lock.l_len= 0;
	lock.l_pid= getpid();
	printf("Entering critical section \n");
	fcntl(fd, F_SETLKW, &lock);
	read(fd, &db2, sizeof(struct db));
	printf("Older ticket count: %d\n", db2.ticket_no);
	db2.ticket_no++;
	lseek(fd, 0, SEEK_SET);
	write(fd, &db2, sizeof(struct db));
	printf("Press key to exit critical section\n");
	getchar();
	lock.l_type= F_UNLCK;
	printf("Lock released\n");
	fcntl(fd, F_SETLK, &lock);
	printf("Updated ticket count is: %d\n", db2.ticket_no);
	close(fd);

}
