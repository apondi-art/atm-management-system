#include "header.h"

sqlite3 *OpenDatabase(const char *filename)
{
    sqlite3 *db;

    int rc = sqlite3_open(filename, &db); // opens database, rc is like error output
    if (rc != SQLITE_OK) {
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

void CreateTables(sqlite3 *db) {
    char *errMsg = 0;

    // SQL command to create the users table
    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT UNIQUE NOT NULL, "
                      "password TEXT NOT NULL);";

    // Execute SQLite command
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {  // Check for errors
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);  // Free error message memory
    } else {
        printf("Users table created successfully!\n");
    }
}
