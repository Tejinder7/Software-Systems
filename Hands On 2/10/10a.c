//Name: Tejinder Singh
//Registration number: MT2022124

//10. Write a separate program using sigaction system call to catch the following signals.
//a. SIGSEGV
//b. SIGINT
//c. SIGFPE

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void print(){
    printf("Caught SIGSEGV\n");
}

int main(void)
{
    int status;
    struct sigaction act;
    
    act.sa_handler= print;//function that replace default action of signal SIGSEGV
    act.sa_flags= 0;
    
    status = sigaction(SIGSEGV, &act, NULL);
    
    if (status == -1)
    {
        perror("Error while assigning signal handler!");
    }
    else
    {
        raise(SIGSEGV);
    }
}
