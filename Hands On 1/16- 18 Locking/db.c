//Name: Tejinder Singh 
//Registration Number: MT202212

//Creating db to use for Mandatory Locking

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;
	struct db{
		int ticket_no;
	}db1;
	db1.ticket_no= 1;
	fd= open("db", O_RDWR| O_CREAT, 0744);
	write(fd, &db1, sizeof(struct db));
	close(fd);
	fd= open("db", O_RDONLY);
	read(fd, &db1, sizeof(struct db));
	printf("Ticket no: %d\n", db1.ticket_no);
	close(fd);
}
