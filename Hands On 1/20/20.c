//Name: Tejinder Singh 
//Registration Number: MT2022124
//
//20. Find out the priority of your running program. Modify the priority with nice command

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>

int main(void){
	printf("The priority of the running process is: %d\n", getpriority(PRIO_PROCESS, 0));
	printf("Modifying the priority of the process by using nice command\n");
	nice(10);
	printf("The modified priority is: %d\n", getpriority(PRIO_PROCESS,0));
}
