//Creating records file to use in Advisory Locking

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void){
	int fd, i;
	struct {
		int train_num;
		int ticket_count;
	} db[3];

	for(i=0; i<3; i++){
		db[i].train_num= i+1;
		db[i].ticket_count= 0;
	}

	for(i=0; i< 3; i++){
		printf("Ticket count of train number %d is %d\n", db[i].train_num, db[i].ticket_count);
	}

	fd= open("records.txt", O_RDWR| O_CREAT, 0744);
	write(fd, db, sizeof(db));
	close(fd);

}
