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


int main() {
    /*
    int clientSocket;
    char message[] = "Hi there you Server!\n";
    struct sockaddr_in serverAddr;

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Send a message to the server
    send(clientSocket, message, sizeof(message) , 0);

    // Close the client socket
    pclose(clientSocket);
    */
    
    int ClientSock;
    char message[] = "Hi there you Server!\n";
    struct sockaddr_in dstAddr;
    
    initSocket(&ClientSock, &dstAddr);
    
    send(ClientSock, message, sizeof(message) , 0);

    close(ClientSock);

    return 0;
}


/* --- FUNCTIONS DEFINITIONS --- */


void initSocket(int* SocketFD, struct sockaddr_in *ServAddr) {
    
    *SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (*SocketFD < 0) {
        perror("socket failed");
        exit(1);
    }

    ServAddr -> sin_family = AF_INET;
    ServAddr -> sin_port = htons(PORT);

    if (inet_pton(AF_INET , SERVER_IP, &(ServAddr -> sin_addr)) 
        <= 0) { 
        perror("Invalid IP Address");
        return;
        }

    if ((connect(*SocketFD, (struct sockaddr*)ServAddr, sizeof(*ServAddr))) < 0) {
            perror("connect failed");
            return;
        }
};