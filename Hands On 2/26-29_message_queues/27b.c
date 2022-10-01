//Name: Tejinder Singh
//Registration number: MT2022124

//27. Write a program to receive messages from the message queue.
//a. with 0 as a flag
//b. with IPC_NOWAIT as a flag

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	key_t key;
	int msgid;
	int result;

	struct msg{
		long int mtype;
		char message[128];
	}mq1;

	key= ftok(".", 'a');
	msgid= msgget(key, 0);

	printf("Enter message type: \n");
	scanf("%ld", &mq1.mtype);

	result= msgrcv(msgid, &mq1, sizeof(mq1.message), mq1.mtype, IPC_NOWAIT);
	if(result== -1){
		printf("Error while receiving the message\n");
		exit(-1);
	}

	printf("Message type: %ld\nMessage: %s\n", mq1.mtype, mq1.message);

}
