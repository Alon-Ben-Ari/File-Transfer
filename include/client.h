#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


/* --- DECLARATIONS ---  */

#define SERVER_IP "127.0.0.1"
#define PORT 49152


void initSocket(int* SocketFD, struct sockaddr_in *ServAddr);


/*  --- END OF DECLARATIONS  ---  */

#endif // CLIENT_HEADER
