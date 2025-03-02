#include "header.h"
int checkCases(sqlite3 *db, int choice)
{
    char name[100];     // Allocate memory for name
    char password[100]; // Allocate memory for password

    switch (choice)
    {
    case 1:
        Print_Login(name, password);
        int result = Login(db, name, password); // Get login result
        fflush(stdout);
        return result; //  Return login success or failure

    case 2:
        Print_Register(name, password);
        Register(db, name, password);
        return 0; //  Ensure registration does not log in automatically

    case 3:
        printf("Exiting program...\n");
        exit(0); //  Exit the program

    default:
        printf("Invalid option. Please try again.\n");
        return 0; //  Ensure invalid input returns 0
    }
}


void Print_Register(char *name, char *password)
{
    clearScreen();
    printf("Bank Management system\n");
    printf("Enter Your Name :");
    scanf("%99s", name);
    printf("\n\n");
    printf("Enter the password to Register:  ");
    scanf("%99s", password);
    printf("\n\n");
}

void Print_Login(char *name, char *password)
{
    clearScreen();
    printf("Bank Management system\n");
    printf("Enter Username :");
    scanf("%99s", name);
    printf("\n\n\n");
    printf("Enter Password:  ");
    scanf("%99s", password);
}

void CaseBankOption(sqlite3 *db, int choice, int User_Id)
{
    char accounN[20]; // Increased size for safety
    char accountT[20];
    char country[50];
    char phone[20];
    double balance = 0.0; // Use double for accurate transactions
    char creationD[20];

    switch (choice)
    {
    case 1:
        clearScreen();
        BankRecords(accounN, accountT, country, phone, &balance, creationD);
        if (CreateAccount(db, User_Id, accounN, accountT, country, phone, balance, creationD) == 0)
        {
            printf("\nNew Record Added Successfully!\n");
        }
        else
        {
            printf("\nFailed to Create Account!\n");
        }

        break;

    case 2:
        Update(db);
        printf("Update Account\n");
        break;
    case 3:
        printf("Check  Account Information Here\n");
        break;
    case 4:
        List_All_UserAccount(db, User_Id);
        break;
    case 5:
        printf(" make transaction\n");
        break;
    case 6:
        printf("remove existing account\n");
        break;
    case 7:
        printf(" Transfer ownership Here\n");
        break;
    case 8:
        exit(0);
        printf(" exit\n");
        break;
    default:
        printf(" Select between 1-8 only\n");
    }
}



// Function to display an error and let the user choose to retry or exit
int handleLoginError()
{
    clearScreen();
    int choice;

    while (1)
    { // Keep looping until valid input is received
        printf("\nUsername or password incorrect. What would you like to do?\n");
        printf("1. Retry Login\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ; // Clear input buffer
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 1)
        {
            return 1; // Retry login
        }
        else if (choice == 2)
        {
            return 0; // Exit program
        }
        else
        {
            clearScreen();
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }
}

void BankRecords(char *Account_Number, char *Account_Type, char *Country, char *Phone, double *Balance, char *Creation_date)
{
    printf("===== New Record Entry =====\n");

    printf("Enter today's date (DD/MM/YYYY): ");
    scanf("%19s", Creation_date); // Prevents overflow

    printf("Enter the account number: ");
    scanf("%19s", Account_Number); //  Prevents overflow

    printf("Enter the country: ");
    scanf("%49s", Country); // Prevents overflow

    printf("Enter the phone number: ");
    scanf("%19s", Phone); // Prevents overflow

    printf("Enter amount to deposit: ");
    scanf("%lf", Balance); // Corrected for double

    // Display Account Type Options
    int account_choice;
    printf("Choose Account Type:\n");
    printf("1. Savings\n");
    printf("2. Current\n");
    printf("3. Fixed01 (1 Year)\n");
    printf("4. Fixed02 (2 Years)\n");
    printf("5. Fixed03 (3 Years)\n");
    printf("Enter your choice (1-5): ");

    while (1)
    {
        // scanf unsuccessful,since no return of 1
        if (scanf("%d", &account_choice) != 1)
        {
            while (getchar() != '\n')
                ; // Clear invalid input
            printf("Invalid input. Please enter a number (1-5): ");
            continue;
        }

        switch (account_choice)
        {
        case 1:
            strcpy(Account_Type, "Savings");
            break;
        case 2:
            strcpy(Account_Type, "Current");
            break;
        case 3:
            strcpy(Account_Type, "Fixed01");
            break;
        case 4:
            strcpy(Account_Type, "Fixed02");
            break;
        case 5:
            strcpy(Account_Type, "Fixed03");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 5: ");
            continue;
        }
        break; // Exit loop if valid choice is selected
    }

    printf("\n New Record Added Successfully!\n");
}

void Update(sqlite3 *db)
{
    char account_number[20]; //  Must be a mutable array
    int choice;
    char phone[20];
    char country[50];

    //  Get the account number
    printf("\nWhat is the Account number you want to change? ");
    scanf("%19s", account_number);

    //  Display options
    printf("\nWhat do you want to update?\n");
    printf("1. Phone Number\n");
    printf("2. Country\n");
    printf("Enter choice: ");

    while (1)
    {
        if (scanf("%d", &choice) != 1) //  Fixed &choice
        {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input. Please enter 1 or 2: ");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\nEnter new Phone Number: ");
            scanf("%19s", phone);
            Update_Phone(db, phone, account_number);
            break;

        case 2:
            printf("\nEnter new Country: ");
            scanf("%49s", country);
            Update_Country(db, country, account_number);
            break;

        default:
            printf(" Invalid choice. Select either 1 or 2: ");
            continue;
        }
        break; //  Exit loop after valid input
    }
}