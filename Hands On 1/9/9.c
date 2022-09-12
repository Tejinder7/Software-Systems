//Name: Tejinder Singh 
//Registration Number: MT2022124

/*9. Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

int main(void){
	int fd;
	struct stat buff;
	int i;

	fd= open("file8", O_RDONLY| O_CREAT, 0744);
	i= fstat(fd, &buff);
	if(i== -1){
		perror("lstat error: ");
		exit(EXIT_FAILURE);
	}
	printf("\tFILE INFORMATION: \n");

	printf("Inode Number:              %d\n", buff.st_ino);
	printf("Number of Hard Links:      %d\n", buff.st_nlink);
       	printf("UID:                       %d\n", buff.st_uid);
	printf("GID:                       %d\n", buff.st_gid);
	printf("Size:                      %d\n", buff.st_size);
	printf("Block size:                %d\n", buff.st_blksize);
	printf("Number of Blocks:          %d\n", buff.st_blocks);
	printf("Time of last file access:  %s\n", ctime(&buff.st_atime));
	printf("Time of last modification: %s\n", ctime(&buff.st_mtime));
	printf("Time of last change:       %s\n", ctime(&buff.st_ctime));

}
