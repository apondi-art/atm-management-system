#include "header.h"

sqlite3 *OpenDatabase(const char *filename)
{
    sqlite3 *db;

    int rc = sqlite3_open(filename, &db); // opens database, rc is like error output
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    else
    {
        printf("Database opened succesfully\n");
    }
    CreateTables(db);
    return db;
}

void CreateTables(sqlite3 *db)
{
    char *errMsg = 0;

    // SQL command to create the users
    const char *CreateUsers = "CREATE TABLE IF NOT EXISTS users ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "name TEXT UNIQUE NOT NULL, "
                              "password TEXT NOT NULL);";
    const char *CreateAccount = "CREATE TABLE IF NOT EXISTS accounts("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "user_id INTEGER NOT NULL,"
                                "account_number TEXT UNIQUE NOT NULL,"
                                "account_type TEXT NOT NULL,"
                                "country TEXT ,"
                                "phone TEXT,"
                                "balance REAL NOT NULL,"
                                "creation_date TEXT NOT NULL,"
                                "FOREIGN KEY (user_id) REFERENCES users(id)"

                                ");";

    // Execute SQLite command for creating users
    int rc = 0;
    rc = sqlite3_exec(db, CreateUsers, 0, 0, &errMsg);

    if (rc != SQLITE_OK)
    { // Check for errors
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg); // Free error message memory
    }
    else
    {
        printf("Users tables successfully!\n");
    }

    // Execute commands for creating accounts
    rc = sqlite3_exec(db, CreateAccount, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error occurs during account creation : %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else
    {
        printf("Account table created succesfully\n");
        sleep(2);
    }
}


void Register(sqlite3 *db, const char *name, const char *password)
{
    if (!db)
    {
        fprintf(stderr, "Database connection is NULL\n");
        return;
    }

    const char *sql = "INSERT INTO users (name, password) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("User registered successfully!\n");
    }

    sqlite3_finalize(stmt);
}

int Login(sqlite3 *db, const char *name, const char *password)
{
    const char *sql = "SELECT password FROM users WHERE name = ?;";
    sqlite3_stmt *stmt;
    int user_id = -1; // default user_id to -1(not found)

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare query: %s\n", sqlite3_errmsg(db));
        return 0; // Return failure
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        user_id = sqlite3_column_int(stmt, 0);
        const char *stored_password = (const char *)sqlite3_column_text(stmt, 0);

        if (stored_password == NULL)
        {
            printf("Error: Password not found.\n");
            fflush(stdout);
            sqlite3_finalize(stmt);
            return 0; // Return failure
        }

        if (strcmp(stored_password, password) == 0)
        {
            printf(" Login successful!\n");
            fflush(stdout);
            sqlite3_finalize(stmt);
            return 1; //  Return success
        }
        else
        {
            printf("Incorrect password!\n");
            fflush(stdout);
            sqlite3_finalize(stmt);
            return 0; //  Return failure
        }
    }
    else
    {
        printf("User not found!\n");
        fflush(stdout);
        sqlite3_finalize(stmt);
        return 0; // Return failure
    }
}

int CreateAccount(sqlite3 *db, int user_ID, const char *Account_Number, const char *Account_Type, char *Country, char *Phone, double Balance, const char *Creation_date)
{
    if (!db)
    {
        fprintf(stderr, "Databaseconnection is NULL\n");
        return -1;
    }
    // query with together with placeholders to avoid sql injection
    const char *sql = "INSERT INTO accounts (user_id, account_number, account_type, country, phone, balance, creation_date) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?);"; //
                                                       // create object stmt
    sqlite3_stmt *stmt;
    // prepared sqlite3 sql query above
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    // binding data
    sqlite3_bind_int(stmt, 1, user_ID);
    sqlite3_bind_text(stmt, 2, Account_Number, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, Account_Type, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, Country, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, Phone, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, Balance);
    sqlite3_bind_text(stmt, 7, Creation_date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    printf("Account created successfully for user ID %d!\n", user_ID);

    sqlite3_finalize(stmt);
    return 0;
}

void List_All_UserAccount(sqlite3 *db, int User_Id)
{

    const char *sql = "SELECT account_number, account_type, country, phone, balance, creation_date "
                      "FROM accounts WHERE user_id = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, User_Id);

    clearScreen(); // Clear screen before displaying accounts (if you have this function)
    printf("\n===== Your Accounts =====\n");

    int hasAccount = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        hasAccount = 1;

        // Get values safely with NULL checks
        const unsigned char *account_number = sqlite3_column_text(stmt, 0);
        const unsigned char *account_type = sqlite3_column_text(stmt, 1);
        const unsigned char *country = sqlite3_column_text(stmt, 2);
        const unsigned char *phone = sqlite3_column_text(stmt, 3);
        double balance = sqlite3_column_double(stmt, 4);
        const unsigned char *creation_date = sqlite3_column_text(stmt, 5);

        printf("Account Number: %s\n", account_number ? (char *)account_number : "N/A");
        printf("Type: %s\n", account_type ? (char *)account_type : "N/A");
        printf("Country: %s\n", country ? (char *)country : "N/A");
        printf("Phone: %s\n", phone ? (char *)phone : "N/A");
        printf("Balance: %.2f\n", balance);
        printf("Created on: %s\n", creation_date ? (char *)creation_date : "N/A");
        printf("------------------------\n");
    }

    if (!hasAccount)
    {
        printf("No accounts found for user ID: %d\n", User_Id);
    }

    sqlite3_finalize(stmt);

    // Wait for user input before returning to the menu
    printf("\nPress Enter to continue...");
    getchar(); // Consume any remaining newline
    getchar(); // Wait for Enter
}

void Update_Phone(sqlite3 *db,  char *Phone, const char *Account_number)
{
    const char *sql = "UPDATE accounts SET phone = ? WHERE account_number = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, Phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, Account_number, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("Error updating phone: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Phone number updated successfully!\n");
    }

    sqlite3_finalize(stmt);
}

void Update_Country(sqlite3 *db,  char *country, const char *Account_number)
{
    const char *sql = "UPDATE accounts SET country = ? WHERE account_number = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, country, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, Account_number, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("Error updating country: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf(" Country updated successfully!\n");
    }

    sqlite3_finalize(stmt);
}


// Function to extract the day from a date string
const char* getDay(const char *creation_date) {
    static char copy[20];  
    strncpy(copy, creation_date, sizeof(copy) - 1);
    copy[sizeof(copy) - 1] = '\0';  

    return strtok(copy, "/");  
}

// Function to return the interest rate and duration for fixed accounts
double Account_Rate(const char *Account_Type, int *years) {
    if (strcmp(Account_Type, "Current") == 0) return 0.0;
    if (strcmp(Account_Type, "Savings") == 0) return 7.0;
    if (strcmp(Account_Type, "Fixed01") == 0) { *years = 1; return 4.0; }
    if (strcmp(Account_Type, "Fixed02") == 0) { *years = 2; return 5.0; }
    if (strcmp(Account_Type, "Fixed03") == 0) { *years = 3; return 8.0; }
    return -1.0;
}

// Function to calculate monthly interest for savings
double get_monthly_interest(double balance, double rate) {
    return (balance * rate) / (12*100);
}

// Function to calculate total interest for fixed accounts
double get_fixed_interest(double balance, double rate, int years) {
    return (balance * rate * years) / 100;
}

// Function to display interest details
void GetAll_interest(double balance, const char *creation_date, const char *Account_Type) {
    int years = 0;
    double rate = Account_Rate(Account_Type, &years);  // Ensure this function is correctly defined

    if (rate == 0.0) {
        printf("You will not get interests because the account is of type current.\n");
        return;
    }

    // Ensure getDay is valid and returns a meaningful value
    const char *day = getDay(creation_date);
    if (!day) {
        printf("Error: Could not extract the day from the creation date.\n");
        return;
    }

    int day_num = atoi(day);
    if (day_num <= 0 || day_num > 31) {
        printf("Error: Invalid day extracted from creation date.\n");
        return;
    }
    double interest = 0.0;

    if (years == 0) { 
        interest = get_monthly_interest(balance, rate);
        printf("You will get $%.2f as interest on day %d of every month.\n", interest, day_num);
    } else {  
        interest = get_fixed_interest(balance, rate, years);
        printf("For %s, you will get $%.2f as interest after %d years.\n", Account_Type, interest, years);
    }
}


//getting account information

void Check_Account(sqlite3 *db, const char *Account_number) {
    const char *sql = "SELECT account_type, country, phone, balance, creation_date "
                      "FROM accounts WHERE account_number = ?;";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind the account number
    sqlite3_bind_text(stmt, 1, Account_number, -1, SQLITE_STATIC);

    // Execute the query
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {  // Row found
        const unsigned char *account_type = sqlite3_column_text(stmt, 0);
        const unsigned char *country = sqlite3_column_text(stmt, 1);
        const unsigned char *phone = sqlite3_column_text(stmt, 2);
        double balance = sqlite3_column_double(stmt, 3);
        const unsigned char *creation_date = sqlite3_column_text(stmt, 4);

        printf("\nAccount Details:\n");
        printf("Account Number: %s\n", Account_number ? Account_number : "N/A");
        printf("Type: %s\n", account_type ? (char *)account_type : "N/A");
        printf("Country: %s\n", country ? (char *)country : "N/A");
        printf("Phone: %s\n", phone ? (char *)phone : "N/A");
        printf("Balance: %.2f\n", balance);
        printf("Created on: %s\n", creation_date ? (char *)creation_date : "N/A");

      
        GetAll_interest(balance, creation_date, account_type);
    } else {
        printf("Account not found.\n");
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Wait for user input before returning
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clear the input buffer
    getchar(); // Wait for Enter
}
