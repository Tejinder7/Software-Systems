#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "userStructure.c"

int main(){
    struct normalUser currentUser;
    int fd= open("normalusers/9988711331", O_RDWR);

    read(fd, &currentUser, sizeof(currentUser));

    for(int i= 0; i< 4; i++){
        printf("%d", currentUser.pin[i]);
    }

}