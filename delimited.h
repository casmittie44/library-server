/***************************************************************
 * Small library for creating and maintaining a sorted "database"
 * of text entries, delimited by '\n'
 * Each of the functions in this library are named using Pascal case
 * with a leading "DD" (short for delimited database).
 ****************************************************************/
#ifndef DELIMITED_DATABASE_H
#define DELIMITED_DATABASE_H
typedef struct {
   char delimiter;
   int numberOfEntries;
   char* fileName;
} DD;

typedef struct {
   char* contents;
} DDEntry;


DD* DDCreateDatabase(const char* fileName, char delimiter);
void DDFreeStructure(DD*);

// Insert a new entry into the database
// Returns 0 on success and -1 on failure
int DDInsertEntry(DD* database, char* entry);

int DDRemoveEntry(DD* database, char* entry, int len);

// Search database for entries containing the string keywordSearch, which has length len.
// This function will return any entries containing the keyword in any of its fields
// as a dynamically allocated char*
// This structure will need to be freed after use
char* DDSearch(DD* database, char* entry, int len);
#endif
