#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "hacking.h"
#define PORT 8080

int main() {
   int sockfd, new_sockfd;
   struct sockaddr_in host_addr, client_addr;
   socklen_t sin_size;
   int recv_length = 1, yes = 1;
   char buffer[1024];

   // Attempt to set up socket
   if((sockfd = socket (PF_INET, SOCK_STREAM, 0)) == -1)
      fatal("could not create socket.");

   if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
      fatal("could not set socket options.");

   host_addr.sin_family = AF_INET;
   host_addr.sin_port = htons(PORT);
   host_addr.sin_addr = INADDR_ANY;
   
