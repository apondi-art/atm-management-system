#include "header.h"


// Define states
typedef enum
{
    STATE_MAIN_MENU,
    STATE_BANKING_MENU,
    STATE_EXIT
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

    ProgrameState state = STATE_MAIN_MENU; // Start in main menu
    int choice;                            // Variable to store user input
    int User_id = 0;                        // Track if user is logged in

    while (state != STATE_EXIT)
    {
        switch (state)
        {
        case STATE_MAIN_MENU:
            printOption(); // Display main menu
            
            // Validate input
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n'); // Clear invalid input
                printf("Invalid input. Please enter a number.\n");
                continue;
            }

            if (choice == 0)
            {
                state = STATE_EXIT;
            }
            else if (choice == 1 || choice == 2 || choice == 3)
            {
                // Attempt login or registration
                User_id = checkCases(db, choice);
                if (User_id > 0)
                {
                    state = STATE_BANKING_MENU;
                }
                else if (User_id == 0 && choice != 2) // If login fails (choice != 2 means not registering)
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
            else
            {
                printf("Invalid option. Please enter 1, 2, or 3.\n");
                sleep(3);
                continue;
            }
            break;

        case STATE_BANKING_MENU:
            PrintBankOptions();

            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n'); // Clear invalid input
                printf("Invalid input. Please enter a number.\n");
                continue;
            }

            if (choice == 0)
            {
                state = STATE_MAIN_MENU; // Go back to main menu
            }
            else
            {
                CaseBankOption(db, choice, User_id);
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
