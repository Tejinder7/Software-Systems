//Name: Tejinder Singh 
//Registration Number: MT2022124

//29. Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>

int main(void){
	pid_t  pid;
        int scheduler;
	struct sched_param params;
	
	pid= getpid();
	scheduler= sched_getscheduler(pid);
	params.sched_priority= 10;

	if(scheduler== SCHED_FIFO){
		printf("Scheduling policy of the current process is FIFO\n");
		printf("Modifying the Scheduling policy\n");
		
		sched_setscheduler(pid, SCHED_RR, &params);
		scheduler= sched_getscheduler(pid);
		
		if(scheduler== SCHED_RR){
                        printf("The policy is modified to Round Robin");
                }
                else{
                        perror("Result");
                }
	}
	else if(scheduler== SCHED_RR){
		printf("Scheduling policy of the current process is Round Robin\n");
		printf("Modifying the Scheduling policy\n");
                
		sched_setscheduler(pid, SCHED_FIFO, &params);
		scheduler= sched_getscheduler(pid);
		
		if(scheduler== SCHED_FIFO){
                        printf("The policy is modified to FIFO");
                }
                else{
                        perror("Result");
                }
	}
	else if(scheduler== SCHED_OTHER){
		printf("Scheduling policy of the current process is other\n");
		printf("Modifying the Scheduling policy\n");
                
		sched_setscheduler(pid, SCHED_RR, &params);
		scheduler= sched_getscheduler(pid);
		
		if(scheduler== SCHED_RR){
                        printf("The policy is modified to Round Robin\n");
		}
		else{
			perror("Result");
		}
	}
}
