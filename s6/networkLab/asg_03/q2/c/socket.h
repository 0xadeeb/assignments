#ifndef SOCKET_H_
#define SOCKET_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define port 8088
#define maxSize 500
typedef enum { ack, seq } frameKind;

typedef struct Frame {
    frameKind kind;
    int seqNo;
    int ackNo;
    char data[500];
} Frame;

#endif // SOCKET_H_
