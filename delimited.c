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

static char DDGoToNextEntry(FILE* fp, char delimiter) {
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

// Ensure that a string ends with a delimiter character
// If it does end with the delimiter, return it
// If not, add the delimiter character and return
static char* AppendDelimiter(char* string, char delimiter) {
   int len = strlen(string);
   int offset = 1;
   char* ret;
   if(len == 0)
      return "";
   // If the string ends with the delimiter, no need to edit string,
   // so set the offset to zero
   if(string[len-1] == delimiter) 
      offset = 0;
   
   ret = (char*)malloc(len+offset);
   strncpy(ret, string, len);
   ret[len+offset] = delimiter;
   return ret;
}

int DDInsertEntry(DD* database, char* entry, int len) {
   int i = 0;
   char buffer, *entryWithDelimiter;
   if(database == NULL)
      return -1;

   // Make sure the entry has a delimiter at the end;
   // this will dynamically allocate a char*, which must be freed
   entryWithDelimiter = AppendDelimiter(entry, database->delimiter);

   FILE* filePointer = fopen(database->fileName, "r+");
   buffer = fgetc(filePointer);

   while(buffer <= entry[i]) {
      // If we get to the end of the file, insert there
      // If fputs returns EOF, then we got an error and so return -1
      if(buffer == EOF)
	 break;

      if(buffer == entry[i]) {
	 i++;
	 buffer = fgetc(filePointer);
      }
      
      buffer = DDGoToNextEntry(filePointer, database->delimiter);
   }	

   // If we have gotten this far, then we have found the first
   // entry with first letter greater than the new element;
   // thus, we want to rewind one character
   fseek(filePointer, -1, SEEK_CUR);
   if(fputs(entryWithDelimiter, filePointer) == EOF) {
      perror("Could not write new entry.");
      free(entryWithDelimiter);
      return -1;
   }

   free(entryWithDelimiter);
   database->numberOfEntries++;
   
   // Close file
   if(fclose(filePointer) == EOF) {
      perror("Could not close database file.");
      return -1;
   }

   else
      return 0;
}

int DDRemoveEntry(char* file, char* entry, int len) {
   return 0;
}

char* DDSearch(char* file, char* entry, int len) {
   return "";
}
