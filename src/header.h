#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> // Fixed typo: "sqlite3.h" should not have quotes

sqlite3* OpenDatabase(const char *filename);
void CreateTablesUser(sqlite3 *db);
void AddTableContent(sqlite3 *db, const char *name, const char *password);
void printOption();
void checkCases(sqlite3 *db, int choice); // Fixed missing parameter
void PrintValue(char *name, char *password); // Fixed incorrect declaration

#endif // HEADER_H
