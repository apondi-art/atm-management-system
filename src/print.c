#include "header.h"

void printOption(){
    clearScreen();
    printf("=======ATM=======\n\n");
    printf("-->>feel free to login/register\n\n");
    printf("[1]- login\n\n");
    printf("[2]- register\n\n");
    printf("[3]- exit\n\n");

}




void PrintBankOptions(){
    clearScreen();
    printf("=======ATM=======\n\n");
    printf("-->>feel free to choose one of the option below <<--\n\n");
    printf("[1]- Create a new account\n\n");
    printf("[2]- Update Information of account\n\n");
    printf("[3]- Check accounts\n\n");
    printf("[4]- Check list of owned account\n\n");
    printf("[5]- Make Transaction\n\n");
    printf("[6]- Remove Existing\n\n");
    printf("[7]- Transfer Ownership\n\n");
    printf("[8]- exit\n\n");

}

void clearScreen(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

}

