//Name: Tejinder Singh 
//Registration Number: MT2022124

//30. Write a program to run a script at a specific time using a Daemon process.

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include <stdlib.h>

int main(void){

  time_t current, dead;
  struct tm *deadline;
  int hour, min, sec;
  time(&current);
  deadline = localtime(&current);

  printf("Enter the time in hour minutes and second : ");
  scanf("%d %d %d", &hour, &min, &sec);
  deadline->tm_hour = hour;
  deadline->tm_min = min;
  deadline->tm_sec = sec;

  dead = mktime(deadline);
	
  int f = fork();
  if(f < 0){
    perror("Error : ");
    exit(0);
  }
  else if(f == 0){
    sleep(1);
    int sid;
    sid = setsid();
    if(sid < 0)
    {
      perror("error : ");
      exit(1);
    }
    umask(0);

    chdir("/");

    do{
      time(&current);
    }
    while(difftime(dead, current) > 0);

    printf("I'm daemon\n");
    printf("Running the shell script\n");
    system("/home/tejinder/Desktop/Software_Systems/30");
    return 0;

  }

  else{
    printf("Killing parent with pid %d\n", getpid());
    exit(0);
  }
}

