#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "delimited.h"
#include "hacking.h"

#define DATABASE "books"
#define PORT 8080

void ManageSocket(int);
void ExecuteInput(int, char*);
DD* database;

int main() {
   database = DDCreateDatabase(DATABASE, '\n');
   int sockfd;
   struct sockaddr_in host_addr;
   int yes = 1;
   printf("Setting up socket.\n");
   
   // Attempt to set up socket
   if((sockfd = socket (PF_INET, SOCK_STREAM, 0)) == -1)
      fatal("could not create socket.");
   if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
      fatal("could not set socket options.");
   host_addr.sin_family = AF_INET;
   host_addr.sin_port = htons(PORT);
   host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if(bind(sockfd, (struct sockaddr*)&host_addr, sizeof(struct sockaddr)) == -1)
      fatal("binding to socket");

   if(listen(sockfd, 5) == -1)
      fatal("listening on socket.");
   printf("Listening...\n");
   ManageSocket(sockfd);
   DDFreeStructure(database);
   return 0;
}

void ManageSocket(int sockfd) {
    char buffer[1024];
    struct sockaddr client_addr;
    socklen_t sinSize = sizeof(struct sockaddr_in);
    int ioSocket; 

    // Each loop we accept one connection, take the needed action,
    // then close the connection
    while(1) {
      ioSocket = accept(sockfd, (struct sockaddr*)&client_addr, &sinSize);
      if(ioSocket == -1)
	 fatal("accepting connection");
      
      int ioLength = send(ioSocket, "Enter 'a' followed by book title:\n", 33, 0);
      printf("Sent %u bytes to client.\n", ioLength);
      ioLength = recv(ioSocket, &buffer, 1024, 0);
      printf("Received %u bytes from client.\n", ioLength);
      printf("Client: %.*s", ioLength, buffer);
      if(ioLength == 0) 
	 continue;

      // Telnet sends a multi-character EOL, so lop it off 
      buffer[ioLength-2] = '\n';
      buffer[ioLength-1] = '\0';
      ExecuteInput(ioSocket, buffer);
      close(ioSocket);
   }
}
   
void ExecuteInput(int socket, char* buffer) {
   // Add element to database
   if(buffer[0] == 'a') {
      DDInsertEntry(database, buffer+2);
   }

   // Check out book
   if(buffer[0] == 'c') {
      // CheckOutBook(buffer+2);
   }

   // Search for book and send result
   if(buffer[0] == 's') {
      //char* searchResult = DDSearch(buffer+2, strlen(buffer+2));
      //ioLength = send(ioSocket, searchResult, strlen(searchResult), 0);
   }

   if(buffer[0] == 'q' || buffer[0] == 'Q') {
      close(socket);
      exit(0);
   }
}
