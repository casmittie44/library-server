#include "delimited.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DD* DDCreateDatabase(const char* fileName, char delimiter) {
   // Try to open the file if it already exists;
   // r+ will fail if the file does not already exist
   FILE* fp = fopen(fileName, "r+");

   // If fp is NULL, the file does not exist, so we need to use w+ option
   if(fp == NULL) {
      fp = fopen(fileName, "w+");
   }
   
   if(fclose(fp) == EOF) {
      perror("Could not close database file.");
      return NULL;
   }

   unsigned int len = strlen(fileName); // Length of filename
   DD* ret = (DD*)malloc(sizeof(DD));
   ret->delimiter = delimiter;
   ret->fileName = (char*)malloc(len);  // Allocate memory for filename
   strncpy(ret->fileName, fileName, len);
   ret->numberOfEntries = 0;
   return ret;
}

void DDFreeStructure(DD* databaseStruct) {
   free(databaseStruct->fileName);
   free(databaseStruct);
}

// Ensure that a string ends with a delimiter character
// If it does end with the delimiter, return it
// If not, add the delimiter character and return
static char* AppendDelimiter(char* string, char delimiter) {
   int len = strlen(string) + 1; // length of string including trailing '\0'
   char* ret;
   if(len == 0)
      return "";

   // If the string ends with the delimiter, no need to edit string,
   // so set the offset to zero
   if(string[len-1] == delimiter){   
       ret = malloc(len);
       strncpy(ret, string,len);
   }

   else {
      ret = (char*)malloc(len+1);
      strncpy(ret, string, len);
      strcat(ret, "\n");
   }
       
   return ret;
}

/*********************************************************
 * Insert a new entry into the database. The data is stored
 * in a flat text file and then indexed. 
 *********************************************************/
int DDInsertEntry(DD* database, char* entry) {
   char *entryWithDelimiter;
   if(database == NULL)
      return -1;

   // Make sure the entry has a delimiter at the end;
   // this will dynamically allocate a char*, which must be freed
   entryWithDelimiter = AppendDelimiter(entry, database->delimiter);
   FILE* filePointer = fopen(database->fileName, "a+");
   fputs(entryWithDelimiter, filePointer);
   free(entryWithDelimiter);
   database->numberOfEntries++;
   
   // Close file
   if(fclose(filePointer) == EOF) {
      perror("Could not close database file.");
      return -1;
   }

   return 0;
}

int DDRemoveEntry(char* file, char* entry, int len) {
   return 0;
}

char* DDSearch(char* file, char* entry, int len) {
   return "";
}

static char GoToNextEntry(FILE* fp, char delimiter) {
   char buffer = fgetc(fp);
   if(fp == NULL)
      perror("Null file pointer in GetNextEntry.");

   // Loop until we hit a delimiter or the end of the file
   while(buffer != delimiter && buffer != EOF) {
      buffer = fgetc(fp);
   }

   // Return the first character of the new entry
   buffer = fgetc(fp);  
   return buffer;
}
