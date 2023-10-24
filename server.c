#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define PORT 49152

/* --- ARGUMENTS DECLARATIONS ---  */

//extern in errno = 0;


void initSocket(int* SocketFD, int* NewSocketFD);
void receive(int* NewSocketFD, char* buffer);
void CloseSocket(int* SocketFD);

/*  --- END OF DECLARATIONS  ---  */

int main() {


int ServerSocket=0, NewSocket=0;
char buffer[BUFFER_SIZE];

initSocket(&ServerSocket, &NewSocket);
receive(&NewSocket, buffer); 
printf("%.*s\n", 20, buffer);
//printf("%s\n", buffer);

CloseSocket(&ServerSocket);
CloseSocket(&NewSocket);


return 0;
}

/* --- FUNCTIONS DEFINITIONS --- */

void initSocket(int* SocketFD, int* NewSocketFD) {
    
    *SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (*SocketFD < 0) {
        perror("Binding Failed");
        exit(1);
    }

    struct sockaddr_in ServerAddr;
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(PORT);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;

    // Set a receive timeout of 100 seconds
    struct timeval timeout;
    timeout.tv_sec = 100;  // 100 seconds
    timeout.tv_usec = 0;
    if (setsockopt(*SocketFD, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt failed");
        exit(1);
    }


    if (bind(*SocketFD, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) < 0) {
        perror("Binding Failed");
        exit(1);
    }

    if (listen(*SocketFD, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening failed");
        exit(1);
    }

    struct sockaddr_in newAddr;
    socklen_t addr_size = sizeof(newAddr);
    if ((*NewSocketFD = 
        accept(*SocketFD, (struct sockaddr*)&newAddr, &addr_size)) < 0) {
            perror("Accept Failed");
        }
};


void CloseSocket(int* SocketFD) {
    if (close(*SocketFD) < 0) {
        perror("Failed to close Socket");
    }
};


void receive(int* NewSocketFD, char* buffer) {
    int RecvResult = recv(*NewSocketFD, buffer, BUFFER_SIZE, 0);

    if (RecvResult < 0) {
        if (errno == EWOULDBLOCK) {
            perror("Receive timeout occurred. No data received.\n");
        } else {
            perror("recv failed");
        }
        exit(1);
    }
    else if (RecvResult == 0) {
        printf("Client closed the connection.\n");
    }
};