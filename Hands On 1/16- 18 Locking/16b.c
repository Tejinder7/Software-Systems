//Name: Tejinder Singh 
//Registration Number: MT2022124

//16. Write a program to perform mandatory locking.
//b.) Implement read lock

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fd;
	struct flock lock;

	fd= open("db", O_RDWR);
	lock.l_type= F_RDLCK;
	lock.l_whence= SEEK_SET;
	lock.l_start= 0;
	lock.l_len= 0;
	lock.l_pid= getpid();
	printf("Trying to Acquire Read Lock\n");
	fcntl(fd, F_SETLKW, &lock);
	printf("Lock Acquired \n");
	printf("Press any key to release lock");
	getchar();
	lock.l_type= F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("Lock Released\nProcess finished\n");
}

