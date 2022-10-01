//Name: Tejinder Singh
//Registration number: MT2022124

//13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.


#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
void main()
{
    pid_t pid;

    pid= getpid();
    printf("Sending the SIGSTOP signal to the current process using kill command\n");
   
    int status = kill(pid, SIGSTOP);
    if (status == -1)
    {
        perror("Error while sending kill signal!");
    }
}
