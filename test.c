#include "delimited.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
   int ret;
   DD* database = DDCreateDatabase("data", '\n');
   printf("Number of entries: %d\n", database->numberOfEntries);
   if(argc > 1) 
      ret = DDInsertEntry(database, argv[1]);
   else
      ret = DDInsertEntry(database, "Scripture and the Authority of God | N. T. Wright | Caleb Smith");

   printf("Number of entries: %d\n", database->numberOfEntries);
   DDFreeStructure(database);
   return 0;
}
