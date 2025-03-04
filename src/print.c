#include "header.h"
#define TERMINAL_WIDTH 80 

void printOption(){
    clearScreen();
    printf("\n\n");
    print_centered("=======ATM=======");
    printf("\n\n");
    print_centered("-->> Feel free to login/register");
    printf("\n\n");
    print_centered(" 1 - Login    ");  //
    print_centered(" 2 - Register ");
    print_centered(" 3 - Exit     ");  // 
    printf("\n\n");

}




void PrintBankOptions(){
    clearScreen();
    printf("\n\n");
    print_centered("=======ATM=======");
    printf("\n\n");
    print_centered("-->>feel free to choose one of the option below <<--");
    printf("\n\n");
    print_centered("  [1]- Create a new account         ");
    print_centered("  [2]- Update Information of account");
    print_centered("  [3]- Check accounts               ");
    print_centered("  [4]- Check list of owned account  ");
    print_centered("  [5]- Make Transaction             ");
    print_centered("  [6]- Remove Existing              ");
    print_centered("  [7]- Transfer Ownership           ");
    print_centered("  [8]- exit                         ");
    printf("\n\n");

}

void clearScreen(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

}


void print_centered(const char *text){
   int text_length = strlen(text);
    int padding = (TERMINAL_WIDTH - text_length) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);

}