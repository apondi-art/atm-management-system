#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> // Fixed typo: "sqlite3.h" should not have quotes
#include <string.h>  // ✅ Include this for strcmp()
void clearScreen();
sqlite3* OpenDatabase(const char *filename);
void CreateTables(sqlite3 *db);
void Register(sqlite3 *db, const char *name, const char *password);
int Login(sqlite3 *db , const char *name, const char *password);
void Print_Register(char *name,char *password);
void Print_Login(char *name, char *password);
int handleLoginError();
void printOption();
void PrintBankOptions();
void BankRecords(char *Account_Number, char *Account_Type, char *Country, char *Phone, double *Balance, char *Creation_date);
int CreateAccount(sqlite3 *db, int user_ID, const char *Account_Number, const char *Account_Type,  char *Country,  char *Phone, double Balance, const char *Creation_date);
int checkCases(sqlite3 *db, int choice); 
void CaseBankOption(sqlite3 *db , int choice,int User_Id);
void List_All_UserAccount(sqlite3 *db, int User_Id);
void Update_Phone(sqlite3 *db, char *Phone, const char *Account_number);
void Update(sqlite3 *db);
void Update_Country(sqlite3 *db, char *country ,const char *Account_number);


#endif // HEADER_H
