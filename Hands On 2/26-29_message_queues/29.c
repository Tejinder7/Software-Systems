//Name: Tejinder Singh
//Registration number: MT2022124

//29. Write a program to remove the message queue.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	int msgid;
	int status;

	printf("Enter Message id to be removed\n");
	scanf("%d", &msgid);

	status= msgctl(msgid, IPC_RMID, NULL);
	if(status!= -1){
		printf("Message queue with id %d removed successfully\n", msgid);
	}
}
