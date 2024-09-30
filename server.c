#include "sockutils.h"

AcceptedSocket acceptedSockets[10];
int acceptedSocketCount = 0;

void* receiveAndPrintData(void*);
void broadcastMessage(int, char*);
void startAcceptingIncomingConnections(int);
void recvAndPrintSeparateThread(AcceptedSocket*);

int main() {
    int sockfd = createIPv4Socket();
    struct sockaddr_in* address = createIPv4Address("", PORT);

    if(bind(sockfd, (struct sockaddr*)address, sizeof(*address)) < 0)
        error("Error in binding.");

    if(listen(sockfd, 10) < 0)
        error("Error in listening.");
    printf("Bounded successfully : %s:%d \n", IP, PORT);


    startAcceptingIncomingConnections(sockfd);
    

    free(address);
    shutdown(sockfd, SHUT_RDWR);
    return 0;
}


void startAcceptingIncomingConnections(int sockfd) {
    while(1) {
        AcceptedSocket* clientSocket = acceptIncomingConnection(sockfd);
        acceptedSockets[acceptedSocketCount++] = *clientSocket;
        printf("CONNECTED NEW FD : %d\n", clientSocket->acceptedfd); // DELETE
        recvAndPrintSeparateThread(clientSocket);
    }
}

void recvAndPrintSeparateThread(AcceptedSocket* clientSocket) {

        pthread_t tid;
        pthread_create(&tid, NULL, receiveAndPrintData, (void*)&clientSocket->acceptedfd);
}

void* receiveAndPrintData(void* arg) {
    int acceptedfd = *((int*)arg);
    char buff[1024] = {0};

    while(1) {
        ssize_t amount_rcv = recv(acceptedfd, buff, 1024, 0);

        if(amount_rcv > 0){
            buff[amount_rcv] = 0;
            printf("Received from Server: %s\n", buff);
            broadcastMessage(acceptedfd, buff);
        }
        if(amount_rcv == 0) 
            break;
        
    }
    printf("%d FD : CONNECTION WAS CLOSED!\n", acceptedfd);
    close(acceptedfd);
}
void broadcastMessage(int sockfd, char* buff) {
    printf("BROADCASTIGN ... \n");// DELETE
    for (int i = 0; i < acceptedSocketCount; i++)
    {
        if(acceptedSockets[i].acceptedfd != sockfd) {
            printf("SENDING \" %s \" TO %d\n", buff, acceptedSockets[i].acceptedfd); // DELETE
            send(acceptedSockets[i].acceptedfd, buff, strlen(buff), 0);
        }
    }
    
}