#include "delimited.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
   int ret;
   DD* database = DDCreateDatabase("data", '\n');
   if(argc > 1) 
      ret = DDInsertEntry(database, argv[1], strlen(argv[1]));
   else
      ret = DDInsertEntry(database, "My name is Inigo Montoya.", strlen(argv[0]));
   printf("Inserted entry with return value: %u\n", ret);
   DDFreeStructure(database);
   return 0;
}
