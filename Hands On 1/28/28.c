//Name: Tejinder Singh 
//Registration Number: MT2022124

//28. Write a program to get maximum and minimum real time priority.


#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

int main(void){
	int max= sched_get_priority_max(SCHED_RR);
	int min= sched_get_priority_min(SCHED_FIFO);
	
	if(min== -1){
		perror("Error while finding min priority:\n");
	}
	else{
		printf("Min priority with RR and FIFO is %d\n", min);
	}
	
	if(max== -1){
                perror("Error while finding max priority:\n");
        }
        else{
                printf("Max priority with RR and FIFO is %d\n", max);
        }


}
