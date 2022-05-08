#include "socket.h"
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <unistd.h>

typedef struct user {
    bool present;
    char name[15];
    struct sockaddr_in *addr;
} user;

int main() {
    int sockfd, client, csize;
    char *password = "password123";
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
    int sockCount = sockfd;
    user *clients = (user *)calloc(25, sizeof(user));
    char buffer[maxSize], msg[maxSize];
    FD_ZERO(&master);
    FD_SET(sockfd, &master);

    while (1) {
        copy = master;
        if (select(FD_SETSIZE, &copy, NULL, NULL, NULL) < 0) {
            perror("Select error\n");
            return -1;
        }
        for (int socket = 0; socket <= sockCount; socket++) {
            if (FD_ISSET(socket, &copy)) {
                if (socket == sockfd) {
                    error(client = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&csize),
                          "Couldn't accept new connetion\n");
                    FD_SET(client, &master);
                    sockCount = client > sockCount ? client : sockCount;
                } else {
                    bzero(buffer, maxSize);
                    if (clients[socket].present) {

                        if (!read(socket, buffer, maxSize)) {
                            FD_CLR(socket, &master);
                            clients[socket].present = false;
                            printf("Disconnected from client %d\n", socket);
                            close(socket);
                            continue;
                        }
                        sprintf(msg, "%s: %s", clients[socket].name, buffer);
                        for (int i = 0; i <= sockCount; i++) {
                            if (i != socket && clients[i].present) {
                                write(i, msg, maxSize);
                            }
                        }
                        if (strcmp(buffer, "Bye\n") == 0) {
                            FD_CLR(socket, &master);
                            clients[socket].present = false;
                            printf("Disconnected from client %d\n", socket);
                            close(socket);
                        }
                    } else {
                        int auth;
                        read(socket, buffer, maxSize);
                        strcpy(clients[socket].name, buffer);
                        bzero(buffer, maxSize);
                        read(socket, buffer, maxSize);
                        if (strcmp(buffer, password)) {
                            auth = 0;
                            write(socket, &auth, sizeof(int));
                            FD_CLR(socket, &master);
                            clients[socket].present = false;
                            close(socket);
                            continue;
                        }
                        auth = 1;
                        write(socket, &auth, sizeof(int));
                        clients[socket].present = true;
                        printf("Server is connected to client %d\n", socket);
                        strcpy(buffer, "Welcome to project COBRA\n\0");
                        write(client, buffer, maxSize);
                    }
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
