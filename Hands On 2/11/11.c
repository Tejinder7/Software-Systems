//Name: Tejinder Singh
//Registration number: MT2022124

//11. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
int main(void)
{
    int status;

    printf("Ignoring the SIGINT signal for 5 seconds\n");
    struct sigaction act;

    act.sa_handler = SIG_IGN; 
    act.sa_flags = 0;
    status = sigaction(SIGINT, &act, NULL);
    if (status == -1)
    {
        perror("Error while assigning signal handler!");
    }
    else
    {
        sleep(5);
    }

    printf("Reseting the default action of the SIGINT signal\n");
    struct sigaction actDefault;

    actDefault.sa_handler = SIG_DFL; // setting default SIGINT
    actDefault.sa_flags = 0;
    status = sigaction(SIGINT, &actDefault,NULL);
    if (status == -1)
    {
        perror("Error while assigning signal handler!");
    }
    else
    {
        sleep(5);
    }
}
