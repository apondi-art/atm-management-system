#include "header.h"

int main() {
    // Open database first
    sqlite3* db = OpenDatabase("atm.db");
    if (db == NULL) {
        fprintf(stderr, "Failed to open database\n");
        return 1;
    }

    int choice; // Variable to store user input
    printOption(); 

    while (1) { // Infinite loop to keep displaying options
       // Display options

        scanf("%d", &choice); // Read user input
        if(choice == 0){
            break;
        }
        checkCases(choice);
       
    }
    sqlite3_close(db);

    return 0;
   
}