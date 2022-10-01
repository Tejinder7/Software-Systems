//Name: Tejinder Singh
//Registration number: MT2022124

//9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int main(void)
{
    __sighandler_t status;

    printf("Ignoring the SIGINT signal for 5 seconds\n");
    status=signal(SIGINT, SIG_IGN);
    
    if (status == SIG_ERR)
    {
        perror("Error while assigning signal handler!");
    }
    else
    {
        sleep(5); // SIGINT will be ingnored for 5 seconds
    }

    printf("Reseting the default action of the SIGINT signal\n");
    status = signal(SIGINT, SIG_DFL);
    if (status == SIG_ERR)
    {
        perror("Error while assigning signal handler!");
    }
    else
    {
        sleep(5); 
    }
}
