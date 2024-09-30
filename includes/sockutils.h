#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define IP "127.0.0.1"
#define PORT 2000

typedef struct {
    int acceptedfd;
    struct sockaddr_in address;
    int error;
    int success;
} AcceptedSocket;

void error(char*);
int createIPv4Socket(void);
AcceptedSocket* acceptIncomingConnection(int);
struct sockaddr_in* createIPv4Address(char*, int);
