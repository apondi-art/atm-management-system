#include "header.h"

void checkCases(int choice) {
    switch(choice) {
        case 1:
            // Login functionality
            break;
        case 2:
            // Register functionality
            break;
        case 3:
            printf("Exiting program...\n");
            exit(0); // This will exit the program
            break;
        default:
            printf("Invalid option. Please try again.\n");
    }
}