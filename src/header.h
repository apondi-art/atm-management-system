#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> // Fixed typo: "sqlite3.h" should not have quotes
#include <string.h>  // ✅ Include this for strcmp()
void clearScreen();
sqlite3* OpenDatabase(const char *filename);
void CreateTablesUser(sqlite3 *db);
void Register(sqlite3 *db, const char *name, const char *password);
void Login(sqlite3 *db , const char *name, const char *password);
void Print_Register(char *name,char *password);
void Print_Login(char *name, char *password);
void printOption();
void PrintBankOptions();
void checkCases(sqlite3 *db, int choice); // Fixed missing parameter


#endif // HEADER_H
