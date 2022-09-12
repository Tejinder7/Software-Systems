//Name: Tejinder Singh 
//Registration Number: MT2022124

//19. Write a program to find out time taken to execute getpid system call. Use time stamp counter.

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long long rdtsc(){
  unsigned long long dst;
  __asm__ __volatile__("rdtsc":"=A"(dst));
  return dst;
}

int main(void){
  long long int start, end;
  start = rdtsc();
  int pid = getpid();
  end = rdtsc();
  int nano = (end-start)/2.9;
  printf("The time to execute getpid() is %d nano seconds\n", nano);
}



