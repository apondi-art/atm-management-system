#include "header.h"

typedef enum
{
    STATE_MAIN_MENU,    // this displays main menu
    STATE_LOGIN,        // handles log in menu
    STATE_BANKING_MENU, // displays bank operations
    STATE_EXIT          // exit program
} ProgrameState;

int main()
{
    // Open database first
    sqlite3 *db = OpenDatabase("atm.db");
    if (db == NULL)
    {
        fprintf(stderr, "Failed to open database\n");
        return 1;
    }
    ProgrameState state = STATE_MAIN_MENU; // This start main menu
    int choice;                            // Variable to store user input   
    int User_id = 0;             // Track if user is logged in

    while (state != STATE_EXIT)
    { // Infinite loop to keep displaying options
        switch (state)
        {
        case STATE_MAIN_MENU:
            printOption(); // will diplay main menu
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("Invalid input . Please enter a number .\n");
                continue;
            }
            if (choice == 0)
            {
                state = STATE_EXIT;
            }
            else
            {
                //attemp log in and extracting 
                User_id = checkCases(db, choice);
                if (User_id > 0)
                {
                    state = STATE_BANKING_MENU;
                }
                else if(User_id == 0 && choice != 2)
                {
                    int retry = handleLoginError();
                    if (retry == 0)
                    {
                        state = STATE_EXIT;
                    }
                    else
                    {
                        state = STATE_MAIN_MENU;
                    }
                }
            }
            break;
        case STATE_BANKING_MENU:
            PrintBankOptions();
            
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("Invalid input. Please enter a number.\n");
                continue;
            }

            if (choice == 0)
            {
                state = STATE_MAIN_MENU;
            }
            else
            {
                CaseBankOption(db, choice,User_id);
            }
            break;

        case STATE_EXIT:
            break;

        default:
            printf("Unknown state! Exiting...\n");
            state = STATE_EXIT;
            break;
        }
    }

    sqlite3_close(db); // Close the database before exiting
    return 0;
}
