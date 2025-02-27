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
    CreateTablesUser(db);
    return db;
}

void CreateTablesUser(sqlite3 *db)
{
    char *errMsg = 0;

    // SQL command to create the users
    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT UNIQUE NOT NULL, "
                      "password TEXT NOT NULL);";

    // Execute SQLite command
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK) { // Check for errors
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg); // Free error message memory
    } else
    {
        printf("Users table created successfully!\n");
    }
}

void AddTableContent(sqlite3 *db, const char *name, const char *password) {
    if (!db) {
        fprintf(stderr, "Database connection is NULL\n");
        return;
    }

    const char *sql = "INSERT INTO users (name, password) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully!\n");
    }

    sqlite3_finalize(stmt);
}






