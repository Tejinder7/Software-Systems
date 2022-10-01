#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	int fd;
	struct db{
		int ticket_no;
	}db1;
	db1.ticket_no= 1;
	fd= open("db", O_RDWR| O_CREAT, 0744);
	perror("fd");
	write(fd, &db1, sizeof(struct db));
	perror("write");
	close(fd);
	fd= open("db", O_RDONLY);
	read(fd, &db1, sizeof(struct db));
	perror("read");
	printf("Ticket no: %d\n", db1.ticket_no);
	close(fd);
	
}
