//Name: Tejinder Singh
//Registration number: MT2022124

//12. Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int main(void)
{
    int pid;
    pid = fork();
    
    if (pid == 0)
    {
        printf("Child pid: %d\n", getpid());
        printf("Parent id= %d\n", getppid()); // as parent terminated we can't get parent id in child process so we will get different value;
        
	int status=kill(getppid(), SIGKILL);
        
	if(status== 0){
            printf("Parent is killed, child is now orphan\n");   
            sleep(5);
	    printf("Parent id: %d\n", getppid());
        }
	else{
            perror("Error while killing parent process!");
        }
    }
    else
    {
        while(1);
    }
    return 0;
}
