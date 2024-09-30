#include "sockutils.h"

void startListeningAndPrintMssgOnThread(int);
void* listenAndPrint(void*);

int main() {

    int sockfd = createIPv4Socket();
    struct sockaddr_in* address = createIPv4Address(IP, PORT);

    if((connect(sockfd, (struct sockaddr*)address, sizeof(*address))) < 0) {
        error("Connecting to the Server.");
    }
    printf("Connected to the Server : %s:%d \n", IP, PORT);


    ssize_t size = 0;
    char* line = NULL;
    printf("Type message (exit) ... \n");


    char* name = NULL;
    size_t nameSize = 0;

    printf("Enter your name\n");
    ssize_t nameCount = getline(&name, &nameSize, stdin);
    name[nameCount-1] = 0;

    startListeningAndPrintMssgOnThread(sockfd);

    char buffer[1024];
    while (1)
    {
        ssize_t read_char = getline(&line, &size, stdin);
     
        if(read_char > 0) {
            line[read_char-1] = 0;
            sprintf(buffer, "%s:%s", name, line);
            if(strcmp(line, "exit") == 0)
                break;
            ssize_t amount_sent = send(sockfd, buffer, strlen(buffer), 0);
        }
    }
    
    free(line);
    free(name);
    free(address);
    close(sockfd);
    return 0;
}

void startListeningAndPrintMssgOnThread(int sockfd) {
    pthread_t tid;

    printf("listening to %d\n", sockfd);
    int* dynSockfd = malloc(sizeof(int));
    *dynSockfd = sockfd;
    pthread_create(&tid, NULL, listenAndPrint, (void*)dynSockfd);
}

void* listenAndPrint(void* arg) {
    int acceptedfd = *((int*)arg);
    free((int*)arg);

    printf("CONVERTED IN THREAD : %d\n", acceptedfd);
    char buff[1024] = {0};

    while(1) {
        ssize_t amount_rcv = recv(acceptedfd, buff, 1024, 0);

        if(amount_rcv > 0){
            buff[amount_rcv] = 0;
            printf("%s\n", buff);
        }
        if(amount_rcv == 0) 
            break;
        
    }
    close(acceptedfd);
}
