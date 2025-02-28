#include "header.h"

void checkCases(sqlite3 *db, int choice)
{
    char name[100];     // Allocate memory for name
    char password[100]; // Allocate memory for password

    switch (choice)
    {
    case 1:
        // Login functionality
     
        Print_Login(name, password);
        Login(db, name, password);
        break;
    case 2:
    
       Print_Register(name,password);
        Register(db, name, password);

        // Register functionality
        break;
    case 3:
        printf("Exiting program...\n");
        exit(0); // Exit the program
    default:
        printf("Invalid option. Please try again.\n");
    }
}

void Print_Register(char *name, char *password){
    clearScreen();
    printf("Bank Management system\n");
    printf("Enter Your Name :");
    scanf("%99s", name);
    printf("\n\n");
    printf("Enter the password to Register:  ");
    scanf("%99s", password);
    printf("\n\n");

}

void Print_Login(char *name, char *password){
    clearScreen();
    printf("Bank Management system\n");
    printf("User Login :");
    scanf("%99s", name);
    printf("\n\n\n");
    printf("Enter the password to login:  ");
    scanf("%99s", password);

}

