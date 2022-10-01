//Name: Tejinder Singh
//Registration number: MT2022124

//28. Write a program to change the exiting message queue permission. (use msqid_ds structure)

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	key_t key;
	int msgid;
	struct msqid_ds mq;
	int status;

	key= ftok(".", 'b');
	msgid= msgget(key, IPC_CREAT| 0700);

	printf("Key is: 0x%0x\nMessage id is: %d\n", key, msgid);

	msgctl(msgid, IPC_STAT, &mq);
	printf("Press any key to change permission\n");
	getchar();

	mq.msg_perm.mode= 0774;
	status= msgctl(msgid, IPC_SET, &mq);
	if(status!= -1){
		printf("Permission changed successfully\n");
	}


}
