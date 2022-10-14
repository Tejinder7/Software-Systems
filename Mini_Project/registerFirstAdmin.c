#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "userStructure.c"

int main()
{
    struct admin currentUser;
    int fd;
    int writeStatus;

    printf("\n\t\t\t\tFirst admin Registration\n\n");
    printf("Enter first name   : ");
    scanf("%s", currentUser.firstName);

    printf("Enter last name    : ");
    scanf("%s", currentUser.lastName);

    printf("Enter mobile number: ");
    for (int i = 0; i < 10; i++)
    {
        scanf("%1d", &currentUser.mobileNumber[i]);
    }

    printf("Enter PIN          : ");
    for (int i = 0; i < 4; i++)
    {
        scanf("%1d", &currentUser.pin[i]);
    }

    char filePath[16] = "admins/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&fileName[i], "%d", currentUser.mobileNumber[i]);
    }

    // Concatenate to generate a proper filePath to store the user details in a file
    strcat(filePath, fileName);
    printf("%s", filePath);

    fd = open(filePath, O_RDWR | O_CREAT | O_EXCL, 0774);
    printf("%d", fd);

    if (fd == -1)
    {
        perror("Error");
    }

    // Writing the structure into the user's file
    writeStatus = write(fd, &currentUser, sizeof(currentUser));

    if (writeStatus == -1)
    {
        printf("\nError in saving user information\n");
        exit(-1);
    }

    printf("User created successfully\n");
    
}