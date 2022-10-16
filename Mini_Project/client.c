#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "userStructure.c"

int registerOrLogin;
int userType;
int menuSelect;
int typeSelect;
int registerCount = 3; // Maximum number of attempts for registration
int loginCount = 3;    // Maximum number of attempts for login
int passwordChangeCount = 3;
bool flag = true;
bool flagExit = false;

void normalUserRegister(int sd);
void jointUserRegister(int sd);
void normalUserLogin(int sd);
void jointUserLogin(int sd);
void adminLogin(int sd);
void depositMoney(int sd);
void withdrawMoney(int sd);
void balanceEnquiry(int sd);
void passwordChange(int sd);
void viewDetails(int sd);
void addUser(int sd);
void deleteUser(int sd);
void modifyAccount(int sd);
void searchDetails(int sd);
void fetchNormalUser(int sd);
void fetchJointUser(int sd);
void registerLoginMenu(int sd);
void mainMenu(int sd);
int compareArrays(int arr1[], int arr2[], int length);

void registerLoginMenu(int sd)
{

    printf("What type of user do you want to continue as?\n\n");
    printf("Press 1 for Normal User\n");
    printf("Press 2 for Joint account user\n");
    printf("Press 3 for Admin\n");
    printf("Press any other key to exit\n");

    scanf("%d", &userType);

    if (userType == 1 || userType == 2)
    {
        printf("\nDo you want to login or register\n");

        printf("Press 1 to login\n");
        printf("Press 2 to register\n");
        printf("Press 3 to Exit\n");

        scanf("%d", &registerOrLogin);

        if (userType == 1 && registerOrLogin == 1)
        {
            normalUserLogin(sd);
        }

        else if (userType == 1 && registerOrLogin == 2)
        {
            normalUserRegister(sd);
            printf("\nYou are now logged in\n");
        }

        else if (userType == 2 && registerOrLogin == 1)
        {
            jointUserLogin(sd);
        }

        else if (userType == 2 && registerOrLogin == 2)
        {
            jointUserRegister(sd);
            printf("\nYou are now logged in\n");
        }
        else if (registerOrLogin == 3)
        {
            printf("Exiting the system\n");
            write(sd, &userType, sizeof(userType));
            write(sd, &registerOrLogin, sizeof(registerOrLogin));
            exit(0);
        }
    }

    else if (userType == 3)
    {
        registerOrLogin = 1;
        adminLogin(sd);
    }

    else
    {
        userType = 4;
        write(sd, &userType, sizeof(userType));
        printf("Exiting the system\n");
        exit(0);
    }
}

void mainMenu(int sd)
{

    printf("\n\t\t\t\tMain menu\n");
    printf("Choose an option\n\n");

    if (userType == 1 || userType == 2)
    {

        printf("Press 1 to Deposit money\n");
        printf("Press 2 to Withdraw money\n");
        printf("Press 3 for Balance enquiry\n");
        printf("Press 4 to Change Password\n");
        printf("Press 5 to View Details\n");
        printf("Press 6 to Logout and Exit\n");

        scanf("%d", &menuSelect);
        write(sd, &menuSelect, menuSelect);
        printf("%d", menuSelect);

        switch (menuSelect)
        {
        case 1:
            depositMoney(sd);
            break;

        case 2:
            withdrawMoney(sd);
            break;

        case 3:
            balanceEnquiry(sd);
            break;

        case 4:
            passwordChange(sd);
            break;

        case 5:
            viewDetails(sd);
            break;

        case 6:
            printf("\nThank you using our services. Exiting the system\n");
            exit(0);

        default:
            printf("\nInvalid input. Please try again with a different input\n");
            mainMenu(sd);
            break;
        }
    }

    else if (userType == 3)
    {
        printf("Press 1 to Add a new user account\n");
        printf("Press 2 to Delete a user account\n");
        printf("Press 3 to Modify a user account\n");
        printf("Press 4 to Search for a specific account details\n");
        printf("Press 5 to Logout and Exit\n");

        scanf("%d", &menuSelect);
        write(sd, &menuSelect, menuSelect);

        switch (menuSelect)
        {
        case 1:
            addUser(sd);
            break;

        case 2:
            deleteUser(sd);
            break;

        case 3:
            modifyAccount(sd);
            break;

        case 4:
            searchDetails(sd);
            break;

        case 5:
            printf("\nThank you using our services. Exiting the system\n");
            close(sd);
            exit(0);
            break;

        default:
            printf("\nInvalid input. Please try again with a different input\n");
            mainMenu(sd);
            break;
        }
    }
}

void normalUserRegister(int sd)
{
    bool result;
    struct normalUser currentUser;

    int confirmPin[4]; // To match with the entered PIN for registration

    while (registerCount > 0)
    {
        if (flag)
        {
            write(sd, &userType, sizeof(userType));
            write(sd, &registerOrLogin, sizeof(registerOrLogin));
        }
        else
        {
            write(sd, &typeSelect, sizeof(typeSelect));
        }

        printf("\n\t\t\t\tNormal User Registration\n");
        printf("\nEnter your details for Registration\n\n");

        printf("Enter First name             : ");
        scanf("%s", currentUser.firstName);

        printf("Enter Last name              : ");
        scanf("%s", currentUser.lastName);

        printf("Enter Mobile number          : ");
        // 1d to take 1 digit as input at each index
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &currentUser.mobileNumber[i]);
        }

        printf("Enter PIN                    : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &currentUser.pin[i]);
        }

        printf("Confirm PIN                  : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &confirmPin[i]);
        }

        printf("Enter intial deposit amount  : ");
        scanf("%f", &currentUser.balance);

        write(sd, &currentUser, sizeof(currentUser));
        write(sd, &confirmPin, sizeof(confirmPin));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nUser created Successfully\n");
            break;
        }

        else
        {
            printf("\nEither you entered wrong PINs or user already exists.\nPlease try again with a different mobile number\n");
            registerCount--;
        }
    }
    if (registerCount == 0)
    {
        printf("Too many attempts\nExiting the system\n");
        if (flag)
        {
            userType = 4;
            write(sd, &userType, sizeof(userType));
            write(sd, &registerOrLogin, sizeof(registerOrLogin));
        }
        else
        {
            typeSelect = 4;
            write(sd, &typeSelect, sizeof(typeSelect));
        }
        exit(-1);
    }
}

void jointUserRegister(int sd)
{
    bool result;
    struct jointUser currentUser;

    int confirmPin[4]; // To match with the entered PIN for registration

    while (registerCount > 0)
    {
        if (flag)
        {
            write(sd, &userType, sizeof(userType));
            write(sd, &registerOrLogin, sizeof(registerOrLogin));
        }
        else
        {
            write(sd, &typeSelect, sizeof(typeSelect));
        }

        printf("\n\t\t\t\tJoint User Registration\n");
        printf("\nEnter your details for Registration\n\n");

        printf("Enter First name of user 1    : ");
        scanf("%s", currentUser.firstName);

        printf("Enter Last name of user 1     : ");
        scanf("%s", currentUser.lastName);

        printf("Enter First name of user 2    : ");
        scanf("%s", currentUser.firstName2);

        printf("Enter Last name of user 2     : ");
        scanf("%s", currentUser.lastName2);

        printf("Enter Mobile number           : ");
        // 1d to take 1 digit as input at each index
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &currentUser.mobileNumber[i]);
        }

        printf("Enter PIN                     : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &currentUser.pin[i]);
        }

        printf("Confirm PIN                   : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &confirmPin[i]);
        }

        printf("Enter intial deposit amount   : ");
        scanf("%f", &currentUser.balance);

        write(sd, &currentUser, sizeof(currentUser));
        write(sd, &confirmPin, sizeof(confirmPin));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nUser created Successfully\n");
            break;
        }

        else
        {
            printf("\nEither you entered wrong PINs or user already exists.\nPlease try again with a different mobile number\n");
            registerCount--;
        }
    }
    if (registerCount == 0)
    {
        printf("Too many attempts\nExiting the system\n");
        if (flag)
        {
            userType = 4;
            write(sd, &userType, sizeof(userType));
            write(sd, &registerOrLogin, sizeof(registerOrLogin));
        }
        else
        {
            typeSelect = 4;
            write(sd, &typeSelect, sizeof(typeSelect));
        }

        exit(-1);
    }
}

void adminRegister(int sd)
{
    bool result;
    struct admin currentUser;

    int confirmPin[4]; // To match with the entered PIN for registration

    while (registerCount > 0)
    {
        write(sd, &typeSelect, sizeof(typeSelect));

        printf("\n\t\t\t\tAdmin Registration\n");
        printf("\nEnter your details for Registration\n\n");

        printf("Enter First name          : ");
        scanf("%s", currentUser.firstName);

        printf("Enter Last name           : ");
        scanf("%s", currentUser.lastName);

        printf("Enter Mobile number       : ");
        // 1d to take 1 digit as input at each index
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &currentUser.mobileNumber[i]);
        }

        printf("Enter PIN                 : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &currentUser.pin[i]);
        }

        printf("Confirm PIN               : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &confirmPin[i]);
        }

        write(sd, &currentUser, sizeof(currentUser));
        write(sd, &confirmPin, sizeof(confirmPin));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nUser created Successfully\n");
            break;
        }

        else
        {
            printf("\nYou entered wrong PINs or user already exists.\nPlease try again with a different mobile number\n");
            registerCount--;
        }
    }
    if (registerCount == 0)
    {
        printf("Too many attempts\nExiting the system\n");
        typeSelect = 4;
        write(sd, &typeSelect, sizeof(typeSelect));
        exit(-1);
    }
}

void normalUserLogin(int sd)
{
    bool result;
    struct normalUser currentUser;

    while (loginCount > 0)
    {
        write(sd, &userType, sizeof(userType));
        write(sd, &registerOrLogin, sizeof(registerOrLogin));

        printf("\n\t\t\t\tNormal User Login\n");
        printf("\nEnter your details to login\n\n");

        printf("Enter your Mobile number: ");
        // 1d to take 1 digit as input at each index
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &currentUser.mobileNumber[i]);
        }

        printf("Enter PIN               : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &currentUser.pin[i]);
        }

        write(sd, &currentUser, sizeof(currentUser));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nYou are now logged in\n");
            break;
        }

        else
        {
            printf("\nWrong login credentials. Please try again.\n");
            loginCount--;
        }
    }
    if (loginCount == 0)
    {
        printf("Too many attempts\nExiting the system\n");
        userType = 4;
        write(sd, &userType, sizeof(userType));
        write(sd, &registerOrLogin, sizeof(registerOrLogin));
        exit(-1);
    }
}

void jointUserLogin(int sd)
{
    bool result;
    struct jointUser currentUser;

    while (loginCount > 0)
    {
        write(sd, &userType, sizeof(userType));
        write(sd, &registerOrLogin, sizeof(registerOrLogin));

        printf("\n\t\t\t\tJoint User Login\n");
        printf("\nEnter your details to login\n\n");

        printf("Enter your Mobile number: ");
        // 1d to take 1 digit as input at each index
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &currentUser.mobileNumber[i]);
        }

        printf("Enter PIN               : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &currentUser.pin[i]);
        }

        write(sd, &currentUser, sizeof(currentUser));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nYou are now logged in\n");
            break;
        }

        else
        {
            printf("\nWrong login credentials. Please try again.\n");
            loginCount--;
        }
    }
    if (loginCount == 0)
    {
        printf("Too many attempts\nExiting the system\n");
        userType = 4;
        write(sd, &userType, sizeof(userType));
        write(sd, &registerOrLogin, sizeof(registerOrLogin));
        exit(-1);
    }
}

void adminLogin(int sd)
{
    bool result;
    struct admin currentUser;

    while (loginCount > 0)
    {
        write(sd, &userType, sizeof(userType));
        write(sd, &registerOrLogin, sizeof(registerOrLogin));

        printf("\n\t\t\t\tAdmin Login\n");
        printf("\nEnter your details to login\n\n");

        printf("Enter your Mobile number: ");
        // 1d to take 1 digit as input at each index
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &currentUser.mobileNumber[i]);
        }

        printf("Enter PIN               : ");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &currentUser.pin[i]);
        }

        write(sd, &currentUser, sizeof(currentUser));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nYou are now logged in\n");
            break;
        }

        else
        {
            printf("\nWrong login credentials. Please try again.\n");
            loginCount--;
        }
    }
    if (loginCount == 0)
    {
        printf("Too many attempts\nExiting the system\n");
        userType = 4;
        write(sd, &userType, sizeof(userType));
        write(sd, &registerOrLogin, sizeof(registerOrLogin));
        exit(-1);
    }
}

void depositMoney(int sd)
{
    float addMoney;
    bool result;
    int lockStatus;

    printf("\n\t\t\t\tDeposit Money\n\n");

    read(sd, &lockStatus, sizeof(lockStatus));
    printf("\nLock status is: %d\n", lockStatus);
    if (lockStatus == -1)
    {
        read(sd, &result, sizeof(result));
        if (userType == 1)
        {
            printf("\nAdmin is currently acessing the file.\nPlease try again after some time");
        }
        else
        {
            printf("\nAdmin or the other user is currently accessing the file. Please try again after some time\n");
        }
    }

    else
    {
        printf("How much money do you want to deposit\n");
        scanf("%f", &addMoney);
        printf("\n");

        write(sd, &addMoney, sizeof(addMoney));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nMoney Deposited successfully. Check balance to confirm deposit\n");
        }
        else
        {
            printf("Some error occured at the server. Please try again after some time\n");
        }
    }
    mainMenu(sd);
}

void withdrawMoney(int sd)
{
    float decrementMoney;
    bool result;
    int lockStatus;

    printf("\n\t\t\tWithdraw Money\n\n");

    read(sd, &lockStatus, sizeof(lockStatus));
    if (lockStatus == -1)
    {
        read(sd, &result, sizeof(result));
        if (userType == 1)
        {
            printf("\nAdmin is currently acessing the file.\nPlease try again after some time");
        }
        else
        {
            printf("\nAdmin or the other user is currently accessing the file. Please try again after some time\n");
        }
    }

    else
    {
        printf("How much money do you want to withdraw\n");
        scanf("%f", &decrementMoney);
        printf("\n");

        write(sd, &decrementMoney, sizeof(decrementMoney));

        read(sd, &result, sizeof(result));

        if (result)
        {
            printf("\nMoney Withdrawed successfully. Check balance to confirm withdrawal\n");
        }
        else
        {
            printf("Some error occured at the server. Please try again after some time\n");
        }
    }

    mainMenu(sd);
}

void balanceEnquiry(int sd)
{
    float balance;
    int lockStatus;

    read(sd, &lockStatus, sizeof(lockStatus));
    if (lockStatus == -1)
    {
        read(sd, &balance, sizeof(balance));
        if (userType == 1)
        {
            printf("\nAdmin is currently acessing the file.\nPlease try again after some time");
        }
        else
        {
            printf("\nAdmin or the other user is currently accessing the file. Please try again after some time\n");
        }
    }

    else
    {
        read(sd, &balance, sizeof(balance));

        printf("\n\t\t\t\tBalance Enquiry\n\n");
        printf("Current balance: %f\n", balance);
    }

    mainMenu(sd);
}

void passwordChange(int sd)
{
    int oldPin[4];
    int newPin[4];
    int confirmPin[4];
    bool result;
    int lockStatus;

    printf("\n\t\t\t\tChange Password\n\n");

    read(sd, &lockStatus, sizeof(lockStatus));
    if (lockStatus == -1)
    {
        read(sd, &result, sizeof(result));
        if (userType == 1)
        {
            printf("\nAdmin is currently acessing the file.\nPlease try again after some time");
        }
        else
        {
            printf("\nAdmin or the other user is currently accessing the file. Please try again after some time\n");
        }
    }

    else
    {
        printf("Enter current PIN: \n");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &oldPin[i]);
        }
        write(sd, &oldPin, sizeof(oldPin));

        printf("Enter new PIN: \n");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &newPin[i]);
        }
        write(sd, &newPin, sizeof(newPin));

        printf("Confirm new PIN: \n");
        for (int i = 0; i < 4; i++)
        {
            scanf("%1d", &confirmPin[i]);
        }
        write(sd, &confirmPin, sizeof(confirmPin));

        read(sd, &result, sizeof(result));
        if (result)
        {
            printf("Password changed succesfully\n");
        }
        else
        {
            printf("Entered wrong PINS. Please try Again\n");
        }
    }
    mainMenu(sd);
}

void viewDetails(int sd)
{
    int lockStatus;
    printf("\n\t\t\t\tAccount Details\n\n");

    read(sd, &lockStatus, sizeof(lockStatus));
    if (lockStatus == -1)
    {
        if (userType == 1)
        {
            struct normalUser currentUser;
            read(sd, &currentUser, sizeof(currentUser));
            printf("\nAdmin is currently acessing the file.\nPlease try again after some time");
        }
        else
        {
            struct jointUser currentUser;
            read(sd, &currentUser, sizeof(currentUser));
            printf("\nAdmin or the other user is currently accessing the file. Please try again after some time\n");
        }
    }
    else
    {
        if (userType == 1)
        {
            fetchNormalUser(sd);
        }
        else if (userType == 2)
        {
            fetchJointUser(sd);
        }
    }

    mainMenu(sd);
}

void addUser(int sd)
{
    bool result;

    printf("\n\t\t\t\tAdding new user\n\n");

    printf("Enter the type of user you want to add\n");
    printf("Press 1 for Normal User\n");
    printf("Press 2 for Joint account user\n");
    printf("Press 3 for Admin\n");
    printf("Press any other key to exit the system\n");

    scanf("%d", &typeSelect);

    if (typeSelect == 1)
    {
        flag = false;
        normalUserRegister(sd);
    }

    else if (typeSelect == 2)
    {
        flag = false;
        jointUserRegister(sd);
    }
    else if (typeSelect == 3)
    {
        adminRegister(sd);
    }
    else
    {
        printf("\nThank you using our services. Exiting the system\n");
        exit(0);
    }
    mainMenu(sd);
}

void deleteUser(int sd)
{
    bool result;
    int mobileNumber[10];
    int lockStatus;

    printf("\n\t\t\t\tDeleting user\n\n");

    printf("Enter the type of user you want delete\n");
    printf("Press 1 for Normal User\n");
    printf("Press 2 for Joint account user\n");
    printf("Press any other key to exit the system\n");

    scanf("%d", &typeSelect);
    if (typeSelect == 1 || typeSelect == 2)
    {
        write(sd, &typeSelect, sizeof(typeSelect));

        printf("\nEnter the mobile number of the account you want to delete\n");
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &mobileNumber[i]);
        }

        write(sd, mobileNumber, sizeof(mobileNumber));

        read(sd, &lockStatus, sizeof(lockStatus));

        if (lockStatus == -1)
        {
            read(sd, &result, sizeof(result));
            printf("\nFile is being used by the account holder.\nPlease try again later\n");
        }

        else
        {
            read(sd, &result, sizeof(result));
            if (result)
            {
                printf("\nAccount deleted successfully\n");
            }
            else
            {
                printf("\nThe mobile number specified does not have an account.\nTry again with a different mobile number\n");
            }
        }
    }
    else
    {
        printf("\nThank you using our services. Exiting the system\n");
        exit(0);
    }
    mainMenu(sd);
}

void modifyAccount(int sd)
{
    bool result;
    int mobileNumber[10];
    int lockStatus;

    printf("\n\t\t\t\tModifying user\n\n");

    printf("Enter the type of user you want to modify\n");
    printf("Press 1 for Normal User\n");
    printf("Press 2 for Joint account user\n");
    printf("Press any other key to exit the system\n");

    scanf("%d", &typeSelect);
    if (typeSelect == 1 || typeSelect == 2)
    {
        write(sd, &typeSelect, sizeof(typeSelect));

        printf("\nEnter the mobile number of the account you want to modify\n");
        for (int i = 0; i < 10; i++)
        {
            scanf("%1d", &mobileNumber[i]);
        }

        write(sd, mobileNumber, sizeof(mobileNumber));

        read(sd, &lockStatus, sizeof(lockStatus));

        if (lockStatus == -1)
        {
            read(sd, &result, sizeof(result));
            printf("\nFile is being used by the account holder.\nPlease try again later\n");
        }

        else
        {
            if (typeSelect == 1)
            {
                struct normalUser currentUser;
                printf("Enter new details of the user\n");

                printf("Enter First name   : ");
                scanf("%s", currentUser.firstName);

                printf("Enter Last name    : ");
                scanf("%s", currentUser.lastName);

                printf("Enter Mobile number: ");
                // 1d to take 1 digit as input at each index
                for (int i = 0; i < 10; i++)
                {
                    scanf("%1d", &currentUser.mobileNumber[i]);
                }
                write(sd, &currentUser, sizeof(currentUser));
            }
            else if (typeSelect == 2)
            {
                struct jointUser currentUser;

                printf("Enter First name of user 1: ");
                scanf("%s", currentUser.firstName);

                printf("Enter Last name of user 1 : ");
                scanf("%s", currentUser.lastName);

                printf("Enter First name of user 2: ");
                scanf("%s", currentUser.firstName2);

                printf("Enter Last name of user 2 : ");
                scanf("%s", currentUser.lastName2);

                printf("Enter Mobile number       : ");
                // 1d to take 1 digit as input at each index
                for (int i = 0; i < 10; i++)
                {
                    scanf("%1d", &currentUser.mobileNumber[i]);
                }
                write(sd, &currentUser, sizeof(currentUser));
            }

            read(sd, &result, sizeof(result));

            if (result)
            {
                printf("\n Account modified successfully");
            }
            else
            {
                printf("\n There is an error.\nPlease try again\n");
            }
        }
    }
    else
    {
        printf("\nThank you using our services. Exiting the system\n");
        exit(0);
    }
    mainMenu(sd);
}

void searchDetails(int sd)
{
    bool result;
    int mobileNumber[10];
    int lockStatus;

    printf("\n\t\t\t\tSearching for a user\n\n");

    printf("Enter the type of user you want to search for\n");
    printf("Press 1 for Normal User\n");
    printf("Press 2 for Joint account user\n");
    printf("Press any other key to exit the system\n");

    scanf("%d", &typeSelect);
    write(sd, &typeSelect, sizeof(typeSelect));

    printf("\nEnter the mobile number of the account you want to search\n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%1d", &mobileNumber[i]);
    }

    write(sd, mobileNumber, sizeof(mobileNumber));

    read(sd, &lockStatus, sizeof(lockStatus));

    if (lockStatus == -1)
    {
        if (userType == 1)
        {
            struct normalUser currentUser;
            read(sd, &currentUser, sizeof(currentUser));
            printf("\nFile is being used by the account holder.\nPlease try again later\n");
        }
        else
        {
            struct jointUser currentUser;
            read(sd, &currentUser, sizeof(currentUser));
            printf("\nFile is being used by the account holder.\nPlease try again later\n");
        }
    }
    else
    {
        if (typeSelect == 1)
        {
            fetchNormalUser(sd);
        }

        else if (typeSelect == 2)
        {
            fetchJointUser(sd);
        }
        else
        {
            printf("\nThank you using our services. Exiting the system\n");
            exit(0);
        }
    }

    mainMenu(sd);
}

void fetchNormalUser(int sd)
{
    struct normalUser currentUser;
    read(sd, &currentUser, sizeof(currentUser));

    printf("Account holder's name   : %s %s\n", currentUser.firstName, currentUser.lastName);
    printf("Registered mobile number: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", currentUser.mobileNumber[i]);
    }
    printf("\n");
    printf("Current Balance         : %f\n", currentUser.balance);
}

void fetchJointUser(int sd)
{
    struct jointUser currentUser;
    read(sd, &currentUser, sizeof(currentUser));

    printf("Account holder 1's name   : %s %s\n", currentUser.firstName, currentUser.lastName);
    printf("Account holder 2's name   : %s %s\n", currentUser.firstName2, currentUser.lastName2);
    printf("Registered mobile number  : ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", currentUser.mobileNumber[i]);
    }
    printf("\n");
    printf("Current Balance           : %f\n", currentUser.balance);
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
    int sd;
    int status;
    struct sockaddr_in server;

    char dataFromServer[128];

    sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("Socket Creation:");
        _exit(0);
    }
    // printf("Client side socket created successfully\n");

    server.sin_family = AF_UNIX;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    status = connect(sd, (struct sockaddr *)&server, sizeof(server));
    if (status == -1)
    {
        printf("Connection error:");
        _exit(0);
    }
    // printf("Connection successfully established\n");

    printf("\t\t\t\t*****\t*****\t*****\t*****\t*****\n");
    printf("\t\t\t\tWelcome to Banking Management System\n");
    printf("\t\t\t\t*****\t*****\t*****\t*****\t*****\n\n\n");

    registerLoginMenu(sd);
    mainMenu(sd);
    close(sd);
}