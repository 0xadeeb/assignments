#include "socket.h"
#include <stdbool.h>
#include <sys/select.h>

int main() {
    int sockfd, client, csize;
    struct sockaddr_in *addr = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in)), cli;

    error(sockfd = socket(AF_INET, SOCK_STREAM, 0), "Couldn't create socket\n");
    printf("Socket created!\n");

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);

    error(bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)), "Couldn't bind the socket\n");
    printf("Socket binded successfully\n");

    error(listen(sockfd, 10), "Couldn't get socket to listening mode\n");
    printf("Socket in listening mode\n");
    csize = sizeof(cli);

    fd_set master, copy;
    int sockCount;
    bool *clients = (bool *)calloc(FD_SETSIZE, sizeof(bool));
    char buffer[maxSize], msg[maxSize];
    FD_ZERO(&master);
    FD_SET(sockfd, &master);

    while (1) {
        copy = master;
        select(FD_SETSIZE, &copy, NULL, NULL, NULL);
        sockCount = FD_SETSIZE;
        if (sockCount < 0) {
            perror("Select error\n");
            return -1;
        }
        for (int socket = 0; socket < sockCount; socket++) {
            if (FD_ISSET(socket, &copy)) {
                if (socket == sockfd) {
                    error(client = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&csize),
                          "Couldn't accept new connetion\n");
                    FD_SET(client, &master);
                    clients[client] = true;
                    printf("Server is connected to client %s::%d, %d\n", inet_ntoa(cli.sin_addr),
                           ntohs(cli.sin_port), client);
                    strcpy(buffer, "Welcome to the chat server!\n\0");
                    write(client, buffer, maxSize);
                } else {
                    bzero(buffer, maxSize);
                    if (!read(socket, buffer, maxSize)) {
                        FD_CLR(socket, &master);
                        clients[socket] = false;
                        printf("Disconnected from client %d\n", socket);
                        close(socket);
                        continue;
                    }
                    sprintf(msg, "Client #%d: %s", socket, buffer);
                    for (int i = 0; i < sockCount; i++) {
                        if (i != socket && clients[i]) {
                            write(i, msg, maxSize);
                        }
                    }
                    if (strcmp(buffer, "Bye\n") == 0) {
                        FD_CLR(socket, &master);
                        clients[socket] = false;
                        printf("Disconnected from client %d\n", socket);
                        close(socket);
                    }
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
