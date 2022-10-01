//Name: Tejinder Singh
//Registration number: MT2022124

//25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
//a. access permission
//b. uid, gid
//c. time of last message sent and received
//d. time of last change in the message queue
//d. size of the queue
//f. number of messages in the queue
//g. maximum number of bytes allowed
//h. pid of the msgsnd and msgrcv

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	key_t key;
	int msgid;

	struct ipc_perm msg_perm;
	struct msqid_ds mq;
	struct msginfo info;

	key= ftok(".", 'a');
	msgid= msgget(key, IPC_CREAT| IPC_EXCL| 0744);
	msgctl(msgid, IPC_STAT, &mq);

	printf("Access Permission:                            %od\n", mq.msg_perm.mode);
   	printf("UID:                                          %d\n", mq.msg_perm.uid);
   	printf("GID:                                          %d\n", mq.msg_perm.gid);
   	printf("Time of last message sent:                    %ld\n", mq.msg_stime);
   	printf("Time of last message received:                %ld\n", mq.msg_rtime);
  	printf("Size of queue:                                %ld\n", mq.__msg_cbytes);
    	printf("Number of messages in the queue:              %ld\n", mq.msg_qnum);
    	printf("Maximum number of bytes allowed in the queue: %ld\n", mq.msg_qbytes);
    	printf("PID of last sent message:                     %d\n", mq.msg_lspid);
    	printf("PID of last received message:                 %d\n", mq.msg_lrpid);
}
