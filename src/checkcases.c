#include "header.h"

void checkCases(sqlite3 *db ,int choice) {
    char name[100]; // Allocate memory for name
    char password[100]; // Allocate memory for password
 

    switch(choice) {
        case 1:
            // Login functionality
            break;
        case 2:
            PrintValue(name, password);
            AddTableContent(db, name, password);
            // Register functionality
            break;
        case 3:
            printf("Exiting program...\n");
            exit(0); // Exit the program
        default:
            printf("Invalid option. Please try again.\n");
    }
}

void PrintValue(char *name, char *password) {
    printf("Enter your name: ");
    scanf("%99s", name); // Use %99s to avoid buffer overflow
    printf("Enter your password: ");
    scanf("%99s", password);
}