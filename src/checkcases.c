#include "header.h"
int checkCases(sqlite3 *db, int choice)
{
    char name[100];     // Allocate memory for name to prevent overflow
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
    printf("\n\n");
    print_centered("Bank Management system");
    printf("\n\n");
    printf("Enter Your Name : ");
    scanf("%99s", name);
    printf("\n");
    printf("Enter the password: ");
    scanf("%99s", password);
    printf("\n\n");
}

void Print_Login(char *name, char *password)
{
    clearScreen();
    printf("\n\n");
    print_centered("Bank Management system");
    printf("\n\n");
    printf("Enter Username :");
    scanf("%99s", name);
    printf("\n\n");
    printf("Enter Password:  ");
    scanf("%99s", password);
}



void CaseBankOption(sqlite3 *db, int choice, int User_Id)
{
    char accounN[20]; 
    char NewOwner[20];
    char accountT[20];
    char country[50];
    char phone[20];
    int newid = 0;
    double balance = 0.0; 
    char creationD[20];

    memset(creationD, 0, sizeof(creationD)); // Clear buffer to avoid garbage data

    switch (choice)
    {
    case 1:
        clearScreen();

        BankRecords(accounN, accountT, country, phone, &balance, creationD);
        
        if (CreateAccount(db, User_Id, accounN, accountT, country, phone, balance, creationD) == 0)
        {
            printf("\n\n");
            print_centered("New Record Added Successfully!");
        }
        else
        {
            printf("\nFailed to Create Account!\n");
        }
        break;

    case 2:
        Update(db, User_Id);
        printf("Update Account\n");
        break;

    case 3:
        printf("Enter account number: ");
        scanf("%19s", accounN);
        while (getchar() != '\n'); // Clear input buffer
        Check_Account(db, User_Id, accounN);
        break;

    case 4:
        List_All_UserAccount(db, User_Id);
        break;

    case 5:
        Transaction(db, User_Id);
        break;

    case 6:
        printf("Enter Account Number: ");
        scanf("%19s", accounN);
        while (getchar() != '\n'); // Clear input buffer
        Remove_Account(db, accounN, User_Id);
        printf("Removed existing account\n");
        break;

    case 7:
        printf("Enter Account number: ");
        scanf("%19s", accounN);
        while (getchar() != '\n'); // Clear input buffer

        printf("Enter New Owner: ");
        scanf("%19s", NewOwner);
        while (getchar() != '\n'); // Clear input buffer

        newid = get_id(db, NewOwner);
        transfer_ownership(db, accounN, newid);
        printf("Transfer ownership successful\n");
        break;

    case 8:
        printf("Exiting...\n");
        exit(0); // Ensures the program exits
        break;

    default:
        printf("Select between 1-8 only\n");
    }
}


// Function to display an error and let the user choose to retry or exit
int handleLoginError()
{
    clearScreen();
    int choice;

    while (1)
    { // Keep looping until valid input is received
        printf("\nUsername or password incorrect\n");
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
    printf("\n\n");
    print_centered("===== New Record Entry =====");
    printf("\n\n");

    printf("Enter today's date (DD/MM/YYYY): ");
    scanf("%19s", Creation_date);
      if (Validate(Creation_date) != 0) 
        {
            printf("Error validating date\n");
            return; // Stop execution if the date is invalid
        }


    printf("Enter the account number: ");
    scanf("%19s", Account_Number);

    printf("Enter the country: ");
    scanf("%49s", Country); //

    printf("Enter the phone number: ");
    scanf("%19s", Phone);

    printf("Enter amount to deposit: $");
    scanf("%lf", Balance);

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

    printf("\nNew Record Added Successfully!\n");
}

void Update(sqlite3 *db, int userid)
{
    char account_number[20]; //  Must be a mutable array
    int choice;
    char phone[20];
    char country[50];

    //  Get the account number
    printf("\nEnter account number: ");
    scanf("%19s", account_number);

    //  Display options
    printf("\nSelect what to update :\n");
    printf("1. Phone Number\n");
    printf("2. Country\n");
    printf("Enter choice: ");

    while (1)
    {
        if (scanf("%d", &choice) != 1) //  Fixed &choice
        {
            while (getchar() != '\n')
                ; // Clear input buffer
            printf("Invalid input. Please enter 1 or 2: ");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\nEnter new Phone Number: ");
            scanf("%19s", phone);
            Update_Phone(db, phone, account_number, userid);
            break;

        case 2:
            printf("\nEnter new Country: ");
            scanf("%49s", country);
            Update_Country(db, country, account_number, userid);
            break;

        default:
            printf(" Invalid choice. Select either 1 or 2: ");
            continue;
        }
        break; //  Exit loop after valid input
    }
}

void Transaction(sqlite3 *db, int userid)
{
    char account_number[20]; //  Must be a mutable array
    int choice;
    double Amount;

    //  Get the account number
    printf("\nAccount Number:");
    scanf("%19s", account_number);

    //  Display options
    printf("\nDo you want ?\n");
    printf("1. Witndraw\n");
    printf("2. Deposit\n");
    printf("Enter choice: ");

    while (1)
    {
        if (scanf("%d", &choice) != 1) //  Fixed &choice
        {
            while (getchar() != '\n')
                ; // Clear input buffer
            printf("Invalid input. Please enter 1 or 2: ");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\nEnter amount: ");
            scanf("%lf", &Amount);
            transaction_withdrawal(db, Amount, account_number, userid);
            break;

        case 2:
            printf("\nEnter amount: ");
            scanf("%lf", &Amount);
            transaction_deposit(db, Amount, account_number, userid);
            break;

        default:
            printf(" Invalid choice. Select either 1 or 2: ");
            continue;
        }
        break; //  Exit loop after valid input
    }
}


int Validate(const char *created_date)
{
    time_t t = time(NULL); // Get current time
    struct tm *tm_now = localtime(&t); // Convert to local time
    
    char date_now[11]; // Buffer to store formatted date
    sprintf(date_now, "%02d/%02d/%04d", 
            tm_now->tm_mday, 
            tm_now->tm_mon + 1, // Month is 0-based, so add 1
            tm_now->tm_year + 1900); // Year is stored as years since 1900

    // Compare the given date with the current date
    if (strcmp(date_now, created_date) == 0)
    {
        printf("Date is valid: %s\n", date_now);
    }
    else
    {
        printf("Date is invalid! Expected: %s, but got: %s\n", date_now, created_date);
    }

    // Pause before exiting
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter key

    return (strcmp(date_now, created_date) == 0) ? 0 : 1; // Return 0 if valid, 1 if invalid
}
