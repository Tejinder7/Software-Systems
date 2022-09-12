//Name: Tejinder Singh 
//Registration Number: MT2022124

/*14 Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

       int main(int argc, char *argv[])
       {
           struct stat sb;
	   int ret;
	   ret= lstat(argv[1], &sb);

	   if (ret == -1) {
               perror("lstat error: ");
               exit(EXIT_FAILURE);
           }
	
           printf("%s is a ", argv[1]);

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device file\n");            break;
           case S_IFCHR:  printf("character device file \n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
       }
