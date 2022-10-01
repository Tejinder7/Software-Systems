//Name: Tejinder Singh
//Registration number: MT2022124

//4. Write a program to measure how much time is taken to execute 100 getppid ( ) system call. Use time stamp counter.

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// using time stamp counter
unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc"
                         : "=A"(dst));
    return dst;
}

int main(void)
{
    long long int start, end;

    start = rdtsc();
    int i = 1;
    while (i <= 100)
    {
        getppid();
        i += 1;
    }

    end = rdtsc();

    printf("Time take to execute 100 getppid() system calls: %llu\n", end - start);
}
