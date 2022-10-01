//Name: Tejinder Singh
//Registration number: MT2022124

//6. Write a simple program to create three threads.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void print()
{
    printf("Printing from thread\n");
}

int main(void)
{
    pthread_t threadID1, threadID2, threadID3;
    int pstatus;
    
    pstatus = pthread_create(&threadID1, NULL, (void *)print, NULL);
    
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

    pstatus = pthread_create(&threadID2, NULL, (void *)print, NULL);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

    pstatus = pthread_create(&threadID2, NULL, (void *)print, NULL);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

    pthread_exit(NULL);
}
