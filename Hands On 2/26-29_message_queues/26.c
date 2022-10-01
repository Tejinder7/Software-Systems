//Name: Tejinder Singh
//Registration number: MT2022124

//26. Write a program to send messages to the message queue. Check $ipcs -q

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main(void){
	int msgid, size;
	key_t key;

	struct msg{
		long int mtype;
		char message[128];
	}mq1;

	key= ftok(".", 'a');
	msgid= msgget(key, IPC_CREAT| 0744);

	printf("Enter the message type:\n");
	scanf("%ld", &mq1.mtype);

	printf("Enter the message text:\n");
	scanf(" %[^\n]", mq1.message);
	size= strlen(mq1.message);

	msgsnd(msgid, &mq1, size+ 1, 0); 

}
