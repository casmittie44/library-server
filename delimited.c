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

void DDFreeStructure(DD* database) {
   free(database->fileName);
   free(database);
}

// Ensure that a string ends with a delimiter character
// If it does end with the delimiter, return it
// If not, add the delimiter character and return

/*********************************************************
 * Insert a new entry into the database. The data is stored
 * in a flat text file and then indexed. 
 *********************************************************/
int DDInsertEntry(DD* database, char* entry) {
   if(database == NULL)
      return -1;

   FILE* filePointer = fopen(database->fileName, "a+");
   fputs(entry, filePointer);
   database->numberOfEntries++;
   
   // Close file
   if(fclose(filePointer) == EOF) {
      perror("Could not close database file.");
      return -1;
   }

   return 0;
}

int DDRemoveEntry(DD* database, char* entry, int len) {
   FILE* filePointer = fopen(database->fileName, "r");
}


// Search database for entries containing the string keywordSearch, which has length len.
// This function will return any entries containing the keyword in any of its fields
char** DDSearch(DD* database, char* keywordSearch, int len) {
   int numMatches=0, searchedEntries=0;
   FILE* fp = fopen(database->fileName, "r");
   while(searchedEntries < database->numberOfEntries) {
      for(int i = 0; i < len; i++) {
	 char character = getc(fp);
	 if(character == keywordSearch[i]) // Continue matching
	    continue;
	 else if(character == EOF)
	    return "";
	 else if(character == keywordSearch[0]) 
	    i = 1;
	 else if(character == database->delimiter)
	    searchedEntries++;
	 else 
	    i = 0;
      }
   }

   if(fclose(fp) == EOF) {
      perror("Could not close database file");
      return -1;
   }
}

// Returns the index of the first character
// of the substring if bigString contains substring
// Returns 0 if bigString does not contain substring
// This function is case-sensitive
static int ContainsSubstring(char* bigString, char* substring) {
   int bigLen = strlen(bigString);
   int subLen = strlen(substring);
   
   for(int start = 0; start < (bigLen - subLen); start++) {
      int count = 0;
      while(bigString[start + count] == substring[count]) {
	 if(count == subLen)
	    return start;
	 else
	    count++;
      }
   }

   return 0;
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

// Read the entire entry that the stream's current position
// is within into the buffer location; at most 'max' characters
// will be read and written into buffer. It is assumed that the
// current position is within an entry; the entry to be read
// will be obtained by decrementing the stream position until
// either the file start or a delimiter is found
static int ReadEntry(FILE* fp, char delimiter,
		       char* buffer, int max) {
   if(fp == NULL)
      perror("Null file pointer in ReadEntry.");

   // Rewind until beginning of file or end of previous entry
   char readChar = fgetc(fp);
   while(readChar != delimiter) {
      if(fseek(fp, -2, SEEK_CUR) != 0)
	 return -1;
      readChar = fgetc(fp);
   }

   // Copy the entry into buffer
   for(int i = 0; i < max; i++) {
      readChar = fgetc(fp);
      if(readChar == EOF) // Error, incomplete entry
	 return -1;
      if(readChar == delimiter) { // Entry write complete
	 buffer[i] = readChar;
	 return 0;
      }

      buffer[i] = readChar;
   }

   return 0;
}
	 
      
   
      
   
   
