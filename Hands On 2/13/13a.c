//Name: Tejinder Singh
//Registration number: MT2022124

//13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

void print()
{
    printf("Received SIGSTOP");
}

int main(void)
{

    __sighandler_t status = signal(SIGSTOP, (void *)print);
    
    if (status == SIG_ERR)
    {
        perror("Error while catching SIGSTOP");
    }
    sleep(15);
}

/* 
    A program cannot catch a SIGSTOP signal.We can conclude this by observing that the custom Handler function is never executed and instead the program is terminated !
    Two signals that cannot be caught or ignored
    SIGSTOP
    SIGKILL
*/
