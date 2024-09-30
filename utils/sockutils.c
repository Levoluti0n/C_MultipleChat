#include "sockutils.h"

void error(char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int createIPv4Socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Creating a socket.");
    }
    return sockfd;
}

struct sockaddr_in* createIPv4Address(char* ip, int port) {
    struct sockaddr_in* address = malloc(sizeof(struct sockaddr_in));

    address->sin_port = htons(port);
    address->sin_family = AF_INET;

    if(!strlen(ip)) 
        address->sin_addr.s_addr = INADDR_ANY;
    else 
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

AcceptedSocket* acceptIncomingConnection(int sockfd) {

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    int clientfd = accept(sockfd, (struct sockaddr*)&clientAddress, &clientAddressSize);

    AcceptedSocket* acceptedSocket = (AcceptedSocket*)malloc(sizeof(AcceptedSocket));
    acceptedSocket->acceptedfd = clientfd;
    acceptedSocket->address = clientAddress;
    acceptedSocket->success = clientfd > 0;

    if(!(acceptedSocket->success))
        acceptedSocket->error = clientfd;

    return acceptedSocket;

}

