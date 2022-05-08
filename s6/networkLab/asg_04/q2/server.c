#include "socket.h"

void getnums(char *buffer, float *n1, float *n2, char *op) {
    bool neg = buffer[0] == '-' ? true : false;
    int i = neg ? 1 : 0;
    float num1 = 0, num2 = 0;
    for (; i < strlen(buffer); i++) {
        if (buffer[i] == ' ')
            break;
        num1 = num1 * 10 + (buffer[i] - 48);
    }
    *n1 = num1 * (neg ? -1 : 1);
    *op = buffer[++i];
    i += 2;
    neg = (buffer[i] == '-') ? true : false;
    i = i + (neg ? 1 : 0);
    for (; i < strlen(buffer); i++) {
        if (buffer[i] == 10)
            break;
        num2 = num2 * 10 + (buffer[i] - 48);
    }
    *n2 = num2 * (neg ? -1 : 1);
}

void mathfn(int sockfd) {
    int len;
    float num1, num2, res;
    char buffer[maxSize], op;
    while (1) {
        strcpy(buffer, "Provide an expression to evaluate orelse exit: ");
        write(sockfd, buffer, maxSize);
        bzero(buffer, maxSize);
        len = read(sockfd, buffer, maxSize);
        if (!len || strcmp(buffer, "Exit\n") == 0) {
            break;
        }
        getnums(buffer, &num1, &num2, &op);

        switch (op) {
        case '+':
            res = num1 + num2;
            write(sockfd, &res, sizeof(float));
            break;
        case '-':
            res = num1 - num2;
            write(sockfd, &res, sizeof(float));
            break;
        case '*':
            res = num1 * num2;
            write(sockfd, &res, sizeof(float));
            break;
        case '/':
            res = num1 / num2;
            write(sockfd, &res, sizeof(float));
            break;
        }
    }
}

int main() {
    int sockfd, newSockfd, csize;
    struct sockaddr_in *addr = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in)), cli;
    pid_t child_pid;
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error(sockfd = socket(AF_INET, SOCK_STREAM, 0), "Couldn't create socket\n");
    printf("Socket created!\n");

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);

    error(bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)), "Couldn't bind the socket\n");
    printf("Socket binded successfully\n");

    error(listen(sockfd, 5), "Couldn't get socket to listening mode\n");
    printf("Socket in listening mode\n");
    csize = sizeof(cli);

    while (1) {
        error(newSockfd = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&csize),
              "Couldn't accept new connetion\n");
        printf("Connected to %s::%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        if ((child_pid = fork()) == 0) {
            mathfn(newSockfd);
            printf("Disonnected from %s::%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
        }
    }
    close(sockfd);
    return 0;
}
