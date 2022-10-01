//Name: Tejinder Singh
//Registration number: MT2022124

//8. Write a separate program using signal system call to catch the following signals.
//a.SIGSEGV
//b.SIGINT
//c.SIGFPE
//d.SIGALRM(use alarm system call)
//e.SIGALRM(use setitimer system call)
//f.SIGVTALRM(use setitimer system call)
//g.SIGPROF(use setitimer system call)

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void print()
{
    printf("SIGINT caught\n");
    _exit(0);
}

int main(void)
{
    __sighandler_t status;

    status = signal(SIGINT, (void *)print);
    if (status == SIG_ERR)
    {
        perror("Error while assigning signal handler!");
    }
    else
    {
        raise(SIGINT); // SIGINT signal is sent to a process by its controlling terminal when a user wishes to interrupt the process
    }
}
