//Name: Tejinder Singh
//Registration number: MT2022124

//24. Write a program to create a message queue and print the key and message queue id.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	key_t key;
	int msgid;

	key= ftok(".", 'a');
	msgid= msgget(key, IPC_CREAT| IPC_EXCL| 0744);

	printf("Key= 0x%0x\t Message queue id=%d\n", key, msgid);

}
