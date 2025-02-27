#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
sqlite3* OpenDatabase(const char *filename);
void CreateTables(sqlite3 *db);
void printOption();
void checkCases();
#endif