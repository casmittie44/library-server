/***************************************************************
 * Small library for creating and maintaining a sorted "database"
 * of text entries, delimited by '\n'
 * Each of the functions in this library are named using Pascal case
 * with a leading "DD" (short for delimited database).
 ****************************************************************/
#ifndef DELIMITED_DATABASE_H
#define DELIMITED_DATABASE_H

typedef struct{
   char delimiter;
   int numberOfEntries;
   char* fileName;
} DD;
   
DD* DDCreateDatabase(const char* fileName, char delimiter);
void DDFreeStructure(DD*);
int DDInsertEntry(DD* database, char* entry, int len);
int DDRemoveEntry(char* file, char* entry, int len);
char* DDSearch(char* file, char* entry, int len);
#endif
