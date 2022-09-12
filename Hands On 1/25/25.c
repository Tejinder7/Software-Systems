//Name: Tejinder Singh 
//Registration Number: MT2022124

//25. Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
	int child, child_1, child_2, child_3;
	int i, status;
	printf("Enter the child you want to wait for: (1, 2 or 3)\n");
	scanf("%d", &i);
	
	child_1= fork();
	if(child_1==0){
		printf("Child 1 is created\n");
		printf("Putting child 1 to sleep for 5 seconds\n\n");
		sleep(5);
		printf("Child 1 is awake and will exit\n");
		exit(0);
	}
	else{
		child_2= fork();
		if(child_2== 0){
			printf("Child 2 is created\n");
			printf("Putting child 2 to sleep for 8 seconds\n\n");
			sleep(8);
			printf("Child 2 is awake and will exit\n");
			exit(0);
		}
		else{
			child_3= fork();
			if(child_3== 0){
				printf("Child 3 is created\n");
				printf("Putting child 3 to sleep for 10 seconds\n\n");
				sleep(10);
				printf("Child 3 is awake and will now exit\n");
				exit(0);
			}
			else{
				//Parent branch
				sleep(1);
				printf("Parent pid = %d\n",getpid());
       				printf("Pid of child 1 = %d\n", child_1);
       	 			printf("Pid of child 2 = %d\n", child_2);
        			printf("Pid of child 3 = %d\n\n", child_3);
				
				if(i==1){
					child= child_1;
				}
				else if(i==2){
					child= child_2;
				}
				else if(i==3){
					child= child_3;
				}

				printf("Parent process waiting for child %d\n", i);
				waitpid(child, &status, 0);

				printf("Child %d with pid %d finished execution\n", i, child);
				printf("Parent process exiting..\n");
			}
		}
	}
}
