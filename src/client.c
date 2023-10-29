#include client.h


int main() {
    
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