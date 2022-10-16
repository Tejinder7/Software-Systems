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
bool addAdmin(int sd, struct admin user1);
struct normalUser getNormalUser(int sd);
struct jointUser getJointUser(int sd);
bool deleteNormalUser(int sd);
bool deleteJointUser(int sd);
bool modifyNormalUser(int sd);
bool modifyJointUser(int sd);
int compareArrays(int arr1[], int arr2[], int length);
void arrayToString(int arr[], char name[]);

int registerOrLogin;
int userType;
int menuSelect;
int fd;
int fd1;
struct flock lock;
bool flag = false;

void serverTasks(int sd)
{
    bool result;

    while (1)
    {
        read(sd, &userType, sizeof(userType));
        
        if (userType == 1)
        {
            struct normalUser currentUser;
            read(sd, &registerOrLogin, sizeof(registerOrLogin));

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
                fd = dup(fd1);
                close(fd1);
                write(sd, &result, sizeof(result));
            }
            else if (registerOrLogin == 3)
            {
                write(1, "\nTerminating connection\n", sizeof("\nTerminating connection\n"));
                exit(0);
            }
        }

        else if (userType == 2)
        {
            read(sd, &registerOrLogin, sizeof(registerOrLogin));
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
                fd = dup(fd1);
                close(fd1);
                write(sd, &result, sizeof(result));
            }
            else if (registerOrLogin == 3)
            {
                write(1, "\nTerminating connection\n", sizeof("\nTerminating connection\n"));
                exit(0);
            }
        }
        else if (userType == 3)
        {
            read(sd, &registerOrLogin, sizeof(registerOrLogin));
            struct admin currentUser;
            read(sd, &currentUser, sizeof(currentUser));

            result = loginAdmin(sd, currentUser);
            write(sd, &result, sizeof(result));
        }
        else if (userType== 4)
        {
            write(1, "\nTerminating connection\n", sizeof("\nTerminating connection\n"));
            exit(0);
        }

        if (result)
        {
            break;
        }
    }

    while (1)
    {
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

            case 6:
                flag = true;
                break;

            default:
                break;
            }
        }

        else if (userType == 3)
        {
            int typeSelect;
            switch (menuSelect)
            {
            case 1:
                while (1)
                {
                    read(sd, &typeSelect, sizeof(typeSelect));
                    if (typeSelect == 1)
                    {

                        struct normalUser currentUser;
                        read(sd, &currentUser, sizeof(currentUser));
                        result = registerNormalUser(sd, currentUser);
                        write(sd, &result, sizeof(result));
                    }

                    else if (typeSelect == 2)
                    {

                        struct jointUser currentUser;
                        read(sd, &currentUser, sizeof(currentUser));
                        result = registerJointUser(sd, currentUser);
                        write(sd, &result, sizeof(result));
                    }
                    else if (typeSelect == 3)
                    {

                        struct admin currentUser;
                        read(sd, &currentUser, sizeof(currentUser));
                        result = addAdmin(sd, currentUser);
                        write(sd, &result, sizeof(result));
                    }
                    else if (typeSelect == 4)
                    {
                        printf("\nAdminside Terminating Connection\n");
                        exit(0);
                    }
                    if (result)
                    {
                        break;
                    }
                }
                break;

            case 2:
                read(sd, &typeSelect, sizeof(typeSelect));

                if (typeSelect == 1)
                {
                    result = deleteNormalUser(sd);
                    write(sd, &result, sizeof(result));
                }
                else if (typeSelect == 2)
                {
                    result = deleteJointUser(sd);
                    write(sd, &result, sizeof(result));
                }
                break;

            case 3:
                read(sd, &typeSelect, sizeof(typeSelect));

                if (typeSelect == 1)
                {
                    result = modifyNormalUser(sd);
                    write(sd, &result, sizeof(result));
                }
                else if (typeSelect == 2)
                {
                    result = modifyJointUser(sd);
                    write(sd, &result, sizeof(result));
                }
                break;

            case 4:
                read(sd, &typeSelect, sizeof(typeSelect));

                if (typeSelect == 1)
                {
                    struct normalUser currentUser;

                    currentUser = getNormalUser(sd);

                    write(sd, &currentUser, sizeof(currentUser));
                }
                else if (typeSelect == 2)
                {
                    struct jointUser currentUser;

                    currentUser = getJointUser(sd);

                    write(sd, &currentUser, sizeof(currentUser));
                }
                break;

            case 5:
                flag = true;
                break;

            default:
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }
}

bool registerNormalUser(int sd, struct normalUser user1)
{
    bool result;
    int confirmPin[4];
    int compareStatus;

    int writeStatus;

    read(sd, &confirmPin, sizeof(confirmPin));
    compareStatus = compareArrays(confirmPin, user1.pin, 4);

    if (!compareStatus)
    {
        return false;
    }

    char filePath[16] = "normalusers/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    arrayToString(user1.mobileNumber, fileName);

    // Concatenate to generate a proper filePath to store the user details in a file
    strcat(filePath, fileName);
    printf("%s", filePath);

    fd1 = open(filePath, O_RDWR | O_CREAT | O_EXCL, 0774);
    printf("%d", fd1);

    if (fd1 == -1)
    {

        // User already exists
        return false;
    }

    // Writing the structure into the user's file
    writeStatus = write(fd1, &user1, sizeof(user1));

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
    int confirmPin[4];
    int compareStatus;

    int writeStatus;

    read(sd, &confirmPin, sizeof(confirmPin));
    compareStatus = compareArrays(confirmPin, user1.pin, 4);

    if (!compareStatus)
    {
        return false;
    }

    char filePath[16] = "jointusers/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    arrayToString(user1.mobileNumber, fileName);

    // Concatenate to generate a proper filePath to store the user details in a file
    strcat(filePath, fileName);
    printf("%s", filePath);

    fd1 = open(filePath, O_RDWR | O_CREAT | O_EXCL, 0774);

    if (fd1 == -1)
    {

        // User already exists
        return false;
    }

    // Writing the structure into the user's file
    writeStatus = write(fd1, &user1, sizeof(user1));

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

    arrayToString(user1.mobileNumber, fileName);

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

    arrayToString(user1.mobileNumber, fileName);

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

    arrayToString(user1.mobileNumber, fileName);

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
    int lockStatus;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));
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

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        printf("Transaction complete\n");
        return true;
    }
    else if (userType == 2)
    {
        struct jointUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));

        currentUser.balance += addMoney;
        lseek(fd, 0L, SEEK_SET);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        printf("Transaction complete\n");
        return true;
    }
}

bool withdrawMoney(int sd)
{
    float decrementMoney;
    int readStatus;
    int writeStatus;
    int lockStatus;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));
    read(sd, &decrementMoney, sizeof(decrementMoney));

    lseek(fd, 0L, SEEK_SET);

    if (userType == 1)
    {
        struct normalUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        if (readStatus)
        {
            if (decrementMoney <= currentUser.balance)
            {
                currentUser.balance -= decrementMoney;
            }
            else
            {
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("Transaction complete\n");
                return false;
            }
        }
        else
        {
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            printf("Transaction complete\n");
            return false;
        }

        lseek(fd, (-1) * sizeof(currentUser), SEEK_CUR);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        printf("Transaction complete\n");
        return true;
    }
    else if (userType == 2)
    {
        struct jointUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));

        if (readStatus)
        {
            if (decrementMoney <= currentUser.balance)
            {
                currentUser.balance -= decrementMoney;
            }
            else
            {
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("Transaction complete\n");
                return false;
            }
        }
        else
        {
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            printf("Transaction complete\n");
            return false;
        }
        lseek(fd, 0L, SEEK_SET);

        writeStatus = write(fd, &currentUser, sizeof(currentUser));
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        printf("Transaction complete\n");
        return true;
    }
}

float checkBalance(int sd)
{
    int amount;
    int readStatus;
    int lockStatus;

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        amount = 0;
        return amount;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    lseek(fd, 0L, SEEK_SET);

    if (userType == 1)
    {
        struct normalUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        amount = currentUser.balance;
    }
    else if (userType == 2)
    {
        struct jointUser currentUser;
        readStatus = read(fd, &currentUser, sizeof(currentUser));
        amount = currentUser.balance;
    }
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Transaction complete\n");
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

    int lockStatus;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is trying to change password\n", sizeof("Checking if other user is trying to change password\n"));
    lockStatus = fcntl(fd, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

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
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            printf("Transaction complete\n");
            return false;
        }
        else
        {
            if (compareNewPin == 0)
            {
                // new and confirm doesn't match
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("Transaction complete\n");
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
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("Transaction complete\n");
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
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            printf("Transaction complete\n");
            return false;
        }
        else
        {
            if (compareNewPin == 0)
            {
                // new and confirm doesn't match
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("Transaction complete\n");
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
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("Transaction complete\n");
                return true;
            }
        }
    }
}

struct normalUser viewDetailsNormalUser(int sd)
{
    struct normalUser currentUser;
    int readStatus;
    int lockStatus;

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));
    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return currentUser;
    }

    lseek(fd, 0L, SEEK_SET);

    readStatus = read(fd, &currentUser, sizeof(currentUser));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Transaction complete\n");
    
    return currentUser;
}

struct normalUser getNormalUser(int sd)
{
    struct normalUser currentUser;
    int readStatus;
    int fd2;
    int lockStatus;

    int mobileNumber[10];

    read(sd, mobileNumber, sizeof(mobileNumber));

    char fileName[11]; // mobileNumber to be used as filename in users directory

    arrayToString(mobileNumber, fileName);

    char path[16] = "normalusers/";
    strcat(path, fileName);

    fd2 = open(path, O_RDWR);
    
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd2, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return currentUser;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    readStatus = read(fd2, &currentUser, sizeof(currentUser));
    lock.l_type = F_UNLCK;
    fcntl(fd2, F_SETLK, &lock);
    printf("Transaction complete\n");
}

struct jointUser getJointUser(int sd)
{
    struct jointUser currentUser;
    int readStatus;
    int fd2;
    int lockStatus;

    int mobileNumber[10];

    read(sd, mobileNumber, sizeof(mobileNumber));

    char fileName[11]; // mobileNumber to be used as filename in users directory

    arrayToString(mobileNumber, fileName);

    char path[16] = "jointusers/";
    strcat(path, fileName);

    fd2 = open(path, O_RDWR);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd2, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return currentUser;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    readStatus = read(fd2, &currentUser, sizeof(currentUser));
    
    lock.l_type = F_UNLCK;
    fcntl(fd2, F_SETLK, &lock);
    printf("Transaction complete\n");
    return currentUser;
}

struct jointUser viewDetailsJointUser(int sd)
{
    struct jointUser currentUser;
    int readStatus;
    int lockStatus;

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fd, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));
    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return currentUser;
    }

    lseek(fd, 0L, SEEK_SET);

    readStatus = read(fd, &currentUser, sizeof(currentUser));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Transaction complete\n");
    
    return currentUser;
}

bool addAdmin(int sd, struct admin user1)
{
    bool result;

    int writeStatus;

    char filePath[16] = "admins/";
    char fileName[11]; // mobileNumber to be used as filename in users directory

    arrayToString(user1.mobileNumber, fileName);

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

bool deleteNormalUser(int sd)
{
    int mobileNumber[10];
    char path[16] = "normalusers/";
    char name[11];
    int deleteStatus;
    int fdDelete;
    int lockStatus;

    read(sd, mobileNumber, sizeof(mobileNumber));

    arrayToString(mobileNumber, name);

    strcat(path, name);
    
    fdDelete= open(path, O_RDWR);
    
    if(fdDelete== -1){
        lockStatus= 0;
        write(sd, &lockStatus, sizeof(lockStatus));
        return false;
    }
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fdDelete, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    close(fdDelete);
    
    deleteStatus = unlink(path);

    if (!deleteStatus)
    {
        write(1, "Deletion Successful", sizeof("Deletion Succesful"));
        return true;
    }
    else
    {
        write(1, "Deletion Failed", sizeof("Deletion Failed"));
        return false;
    }
}

bool deleteJointUser(int sd)
{
    int mobileNumber[10];
    char path[16] = "jointusers/";
    char name[11];
    int deleteStatus;
    int fdDelete;
    int lockStatus;

    read(sd, mobileNumber, sizeof(mobileNumber));

    arrayToString(mobileNumber, name);

    strcat(path, name);

    fdDelete= open(path, O_RDWR);
    
    if(fdDelete== -1){
        lockStatus= 0;
        write(sd, &lockStatus, sizeof(lockStatus));
        return false;
    }
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fdDelete, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    close(fdDelete);

    deleteStatus = unlink(path);

    if (!deleteStatus)
    {
        write(1, "Deletion Successful", sizeof("Deletion Succesful"));
        return true;
    }
    else
    {
        write(1, "Deletion Failed", sizeof("Deletion Failed"));
        return false;
    }
}

bool modifyNormalUser(int sd)
{
    struct normalUser newCurrentUser;
    struct normalUser oldCurrentUser;
    int mobileNumber[10];
    int fdModify;
    char path1[16] = "normalusers/";
    char name[11];
    char name2[11];
    int lockStatus;

    read(sd, mobileNumber, sizeof(mobileNumber));

    arrayToString(mobileNumber, name);

    strcat(path1, name);

    fdModify = open(path1, O_RDWR);


    if (fdModify == -1)
    {
        lockStatus= 0;
        write(sd, &lockStatus, sizeof(lockStatus));
        write(1, "File does not exist\n", sizeof("File does not exist"));
        return false;
    }
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fdModify, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    lseek(fdModify, 0L, SEEK_SET);

    read(fdModify, &oldCurrentUser, sizeof(oldCurrentUser));

    close(fdModify);
    unlink(path1);
    
    read(sd, &newCurrentUser, sizeof(newCurrentUser));

    for (int i = 0; i < 4; i++)
    {
        newCurrentUser.pin[i] = oldCurrentUser.pin[i];
    }

    newCurrentUser.balance = oldCurrentUser.balance;

    arrayToString(newCurrentUser.mobileNumber, name2);

    char path2[16] = "normalusers/";

    strcat(path2, name2);

    fdModify = open(path2, O_RDWR | O_CREAT | O_EXCL, 0744);
    if (fdModify == -1)
    {
        write(1, "File with new mobile number already exists", sizeof("File with new mobile number already exists"));
        return false;
    }
    write(fdModify, &newCurrentUser, sizeof(newCurrentUser));
    close(fdModify);
    return true;
}

bool modifyJointUser(int sd)
{
    struct jointUser newCurrentUser;
    struct jointUser oldCurrentUser;
    int mobileNumber[10];
    int fdModify;
    char path1[16] = "jointusers/";
    char name[11];
    char name2[11];
    int lockStatus;

    read(sd, mobileNumber, sizeof(mobileNumber));
    
    arrayToString(mobileNumber, name);

    strcat(path1, name);

    fdModify = open(path1, O_RDWR);

    if (fdModify == -1)
    {
        lockStatus= 0;
        write(sd, &lockStatus, sizeof(lockStatus));
        write(1, "File does not exist\n", sizeof("File does not exist"));
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    write(1, "Checking if other user is doing any transaction\n", sizeof("Checking if other user is doing any transaction\n"));
    lockStatus = fcntl(fdModify, F_SETLK, &lock);

    write(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        write(1, "File locked\n", sizeof("File locked\n"));
        return false;
    }

    write(1, "Ready for transaction \n", sizeof("Ready for transaction \n"));

    lseek(fdModify, 0L, SEEK_SET);

    read(fdModify, &oldCurrentUser, sizeof(oldCurrentUser));

    close(fdModify);
    unlink(path1);

    read(sd, &newCurrentUser, sizeof(newCurrentUser));

    for (int i = 0; i < 4; i++)
    {
        newCurrentUser.pin[i] = oldCurrentUser.pin[i];
    }

    newCurrentUser.balance = oldCurrentUser.balance;

    arrayToString(newCurrentUser.mobileNumber, name2);

    char path2[16] = "jointusers/";

    strcat(path2, name2);

    fdModify = open(path2, O_RDWR | O_CREAT | O_EXCL, 0744);
    if (fdModify == -1)
    {
        write(1, "File with new mobile number already exists", sizeof("File with new mobile number already exists"));
        return false;
    }
    write(fdModify, &newCurrentUser, sizeof(newCurrentUser));
    close(fdModify);
    return true;
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

void arrayToString(int arr[], char name[])
{
    for (int i = 0; i < 10; i++)
    {
        // sprintf will store the integers as a string in buffer fileName
        sprintf(&name[i], "%d", arr[i]);
    }
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
            write(1, "Connection successful\n", sizeof("Connection successful\n"));
            serverTasks(nsd);
            write(1, "\nConnection Terminated", sizeof("\nConnection Terminated"));
            close(nsd);
            exit(0);
        }

        else
        {
            close(nsd);
        }
    }
}