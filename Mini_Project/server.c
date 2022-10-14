#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "userStructure.c"

void serverTasks(int sd);
bool registerNormalUser(int sd, struct normalUser user1);
bool registerJointUser(int sd, struct jointUser user1);
bool loginNormalUser(int sd, struct normalUser user1);
bool loginJointUser(int sd, struct jointUser user1);
bool loginAdmin(int sd, struct admin user1);
bool depositMoney(int sd);
bool withdrawMoney(int sd);
struct normalUser viewDetailsNormalUser(int sd);
struct jointUser viewDetailsJointUser(int sd);
bool passwordChange(int sd);
float checkBalance(int sd);
int compareArrays(int arr1[], int arr2[], int length);

int registerOrLogin;
int userType;
int menuSelect;
int fd;

void serverTasks(int sd)
{
    bool result;

    while (1)
    {
        read(sd, &userType, sizeof(userType));
        read(sd, &registerOrLogin, sizeof(registerOrLogin));

        if (userType == 1)
        {
            struct normalUser currentUser;

            if (registerOrLogin == 1)
            {
                read(sd, &currentUser, sizeof(currentUser));

                result = loginNormalUser(sd, currentUser);
                write(sd, &result, sizeof(result));
            }

            else if (registerOrLogin == 2)
            {
                read(sd, &currentUser, sizeof(currentUser));

                result = registerNormalUser(sd, currentUser);
                write(sd, &result, sizeof(result));
            }
        }

        else if (userType == 2)
        {
            struct jointUser currentUser;

            if (registerOrLogin == 1)
            {
                read(sd, &currentUser, sizeof(currentUser));

                result = loginJointUser(sd, currentUser);
                write(sd, &result, sizeof(result));
            }

            else if (registerOrLogin == 2)
            {
                read(sd, &currentUser, sizeof(currentUser));

                result = registerJointUser(sd, currentUser);
                write(sd, &result, sizeof(result));
            }
        }
        else
        {
            struct admin currentUser;
            read(sd, &currentUser, sizeof(currentUser));

            result = loginAdmin(sd, currentUser);
            write(sd, &result, sizeof(result));
        }
        if (result)
        {
            break;
        }
    }

    read(sd, &menuSelect, sizeof(menuSelect));
    if (userType == 1 || userType == 2)
    {
        switch (menuSelect)
        {
        case 1:
            result = depositMoney(sd);
            write(sd, &result, sizeof(result));
            break;
        case 2:
            result = withdrawMoney(sd);
            write(sd, &result, sizeof(result));
            break;
        case 3:
            float balance;
            balance = checkBalance(sd);
            write(sd, &balance, sizeof(balance));
            break;
        case 4:
            result = passwordChange(sd);
            write(sd, &result, sizeof(result));
            break;

        case 5:
            if (userType == 1)
            {
                struct normalUser currentUser;
                currentUser = viewDetailsNormalUser(sd);
                write(sd, &currentUser, sizeof(currentUser));
            }
            else if (userType == 2)
            {
                struct jointUser currentUser;
                currentUser = viewDetailsJointUser(sd);
                write(sd, &currentUser, sizeof(currentUser));
            }
            break;

        default:
            break;
        }
    }
}

bool registerNormalUser(int sd, struct normalUser user1)
{
    bool result;

    int writeStatus;

    char filePath[16] = "normalusers/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&fileName[i], "%d", user1.mobileNumber[i]);
    }

    // Concatenate to generate a proper filePath to store the user details in a file
    strcat(filePath, fileName);
    printf("%s", filePath);

    fd = open(filePath, O_RDWR | O_CREAT | O_EXCL, 0774);
    printf("%d", fd);

    if (fd == -1)
    {

        // User already exists
        return false;
    }

    // Writing the structure into the user's file
    writeStatus = write(fd, &user1, sizeof(user1));

    if (writeStatus == -1)
    {
        printf("\nError in saving user information\n");
        exit(-1);
    }

    // User created successfully
    return true;
}

bool registerJointUser(int sd, struct jointUser user1)
{
    bool result;

    int writeStatus;

    char filePath[16] = "jointusers/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&fileName[i], "%d", user1.mobileNumber[i]);
    }

    // Concatenate to generate a proper filePath to store the user details in a file
    strcat(filePath, fileName);
    printf("%s", filePath);

    fd = open(filePath, O_RDWR | O_CREAT | O_EXCL, 0774);

    if (fd == -1)
    {

        // User already exists
        return false;
    }

    // Writing the structure into the user's file
    writeStatus = write(fd, &user1, sizeof(user1));

    if (writeStatus == -1)
    {
        printf("\nError in saving user information\n");
        exit(-1);
    }

    // User created successfully
    return true;
}

bool loginNormalUser(int sd, struct normalUser user1)
{
    bool result;
    int pinConfirm;

    struct normalUser currentUser;

    char filePath[16] = "normalusers/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&fileName[i], "%d", user1.mobileNumber[i]);
    }

    strcat(filePath, fileName);
    printf("%s", filePath);

    fd = open(filePath, O_RDWR);

    if (fd == -1)
    {
        // Mobile number unregistered
        return false;
    }

    read(fd, &currentUser, sizeof(currentUser));
    pinConfirm = compareArrays(currentUser.pin, user1.pin, 4);

    if (pinConfirm == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool loginJointUser(int sd, struct jointUser user1)
{
    bool result;
    int pinConfirm;

    struct jointUser currentUser;

    char filePath[16] = "jointusers/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&fileName[i], "%d", user1.mobileNumber[i]);
    }

    strcat(filePath, fileName);
    printf("%s", filePath);

    fd = open(filePath, O_RDWR);

    if (fd == -1)
    {
        // Mobile number unregistered
        return false;
    }

    read(fd, &currentUser, sizeof(currentUser));
    pinConfirm = compareArrays(currentUser.pin, user1.pin, 4);

    if (pinConfirm == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool loginAdmin(int sd, struct admin user1)
{
    bool result;
    int pinConfirm;

    struct admin currentUser;

    char filePath[16] = "admins/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&fileName[i], "%d", user1.mobileNumber[i]);
    }

    strcat(filePath, fileName);
    printf("%s", filePath);

    fd = open(filePath, O_RDWR);

    if (fd == -1)
    {
        // Mobile number unregistered
        return false;
    }

    read(fd, &currentUser, sizeof(currentUser));
    pinConfirm = compareArrays(currentUser.pin, user1.pin, 4);

    if (pinConfirm == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool depositMoney(int sd)
{
    float addMoney;
    int readStatus;
    int writeStatus;

    read(sd, &addMoney, sizeof(addMoney));

    lseek(fd, 0L, SEEK_SET);

    if (userType == 1)
    {
        struct normalUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        if (readStatus)
        {
            currentUser.balance += addMoney;
        }

        lseek(fd, (-1) * sizeof(currentUser), SEEK_CUR);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));
        return true;
    }
    else if (userType == 2)
    {
        struct jointUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));

        currentUser.balance += addMoney;
        lseek(fd, 0L, SEEK_SET);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));
        return true;
    }
}

bool withdrawMoney(int sd)
{
    float decrementMoney;
    int readStatus;
    int writeStatus;

    read(sd, &decrementMoney, sizeof(decrementMoney));

    lseek(fd, 0L, SEEK_SET);

    if (userType == 1)
    {
        struct normalUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        if (readStatus)
        {
            currentUser.balance -= decrementMoney;
        }

        lseek(fd, (-1) * sizeof(currentUser), SEEK_CUR);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));
        return true;
    }
    else if (userType == 2)
    {
        struct jointUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));

        currentUser.balance -= decrementMoney;
        lseek(fd, 0L, SEEK_SET);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));
        return true;
    }
}

float checkBalance(int sd)
{
    int amount;
    int readStatus;

    lseek(fd, 0L, SEEK_SET);

    if (userType == 1)
    {
        struct normalUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        amount = currentUser.balance;
    }
    else if (userType == 2)
    {
        struct normalUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        amount = currentUser.balance;
    }
    return amount;
}

bool passwordChange(int sd)
{
    int pin[4];
    int newPin[4];
    int confirmPin[4];
    int readStatus;
    int compareResult;
    int compareNewPin;

    lseek(fd, 0L, SEEK_SET);

    read(sd, &pin, sizeof(pin));
    if (userType == 1)
    {
        struct normalUser currentUser;
        read(fd, &currentUser, sizeof(currentUser));
        compareResult = compareArrays(pin, currentUser.pin, 4);

        read(sd, &newPin, sizeof(newPin));
        read(sd, &confirmPin, sizeof(confirmPin));

        compareNewPin = compareArrays(newPin, confirmPin, 4);
        if (compareResult == 0)
        {
            // wrong old pin
            return false;
        }
        else
        {
            if (compareNewPin == 0)
            {
                // new and confirm doesn't match
                return false;
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    currentUser.pin[i] = newPin[i];
                }
                lseek(fd, 0L, SEEK_SET);
                write(fd, &currentUser, sizeof(currentUser));
                return true;
            }
        }
    }
    else if (userType == 2)
    {
        struct jointUser currentUser;
        read(fd, &currentUser, sizeof(currentUser));
        compareResult = compareArrays(pin, currentUser.pin, 4);

        read(sd, &newPin, sizeof(newPin));
        read(sd, &confirmPin, sizeof(confirmPin));

        compareNewPin = compareArrays(newPin, confirmPin, 4);
        if (compareResult == 0)
        {
            // wrong old pin
            return false;
        }
        else
        {
            if (compareNewPin == 0)
            {
                // new and confirm doesn't match
                return false;
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    currentUser.pin[i] = newPin[i];
                }
                lseek(fd, 0L, SEEK_SET);
                write(fd, &currentUser, sizeof(currentUser));
                return true;
            }
        }
    }
}

struct normalUser viewDetailsNormalUser(int sd)
{
    struct normalUser currentUser;
    int readStatus;

    lseek(fd, 0L, SEEK_SET);

    readStatus = read(fd, &currentUser, sizeof(currentUser));
    printf("%s", currentUser.firstName);
    return currentUser;
}
struct jointUser viewDetailsJointUser(int sd)
{
    struct jointUser currentUser;
    int readStatus;

    lseek(fd, 0L, SEEK_SET);

    readStatus = read(fd, &currentUser, sizeof(currentUser));
    printf("%s", currentUser.firstName);
    return currentUser;
}

int compareArrays(int arr1[], int arr2[], int length)
{

    for (int i = 0; i < length; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int sd, nsd;
    // nsd is the new socket descriptor that will be received after connection
    int bindStatus;
    int listenStatus;
    int clientSize;
    char dataFromClient[128];

    struct sockaddr_in server, client;

    sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("Socket Creation:");
        _exit(-1);
    }
    printf("Socket created successfully\n");

    server.sin_family = AF_UNIX;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bindStatus = bind(sd, (struct sockaddr *)&server, sizeof(server));
    if (bindStatus == -1)
    {
        perror("Bind error:");
        _exit(0);
    }
    printf("Binding successful\n");

    listenStatus = listen(sd, 5);
    if (listenStatus == -1)
    {
        perror("Listen() error:");
        _exit(0);
    }
    printf("Listening for a socket ...\n");

    while (1)
    {

        clientSize = (int)sizeof(client);
        nsd = accept(sd, (struct sockaddr *)&client, &clientSize);
        if (nsd == -1)
        {
            perror("Connection error:");
            _exit(0);
        }

        if (!fork())
        {

            close(sd);
            serverTasks(nsd);
            exit(0);
        }

        else
        {
            close(nsd);
        }
    }
}