#include "socket.h"

void sendVideo(int sockfd, char *buffer, FILE *fp) {
    ssize_t n = 0, total = 0, data = 0;
    long time, start;
    FILE *graph = fopen("graph.txt", "w");
    bzero(buffer, maxSize);
    start = clock();
    time = start;
    while (fread(buffer, sizeof(char), maxSize, fp) > 0) {
        data = send(sockfd, buffer, maxSize, 0);
        total += data;
        n += data;
        bzero(buffer, maxSize);
        if (clock() >= time + CLOCKS_PER_SEC / 100) {
            time = clock();
            fprintf(graph, "%.4lf\t%ld\n",
                    (double)(((double)time - (double)start) / (double)CLOCKS_PER_SEC), n);
            n = 0;
        }
    }
    strcpy(buffer, "Transfer done\n");
    write(sockfd, buffer, maxSize);
    fclose(graph);
}

void chat(int sockfd) {
    char buffer[maxSize];
    FILE *fp;
    while (1) {
        bzero(buffer, maxSize);
        if (read(sockfd, buffer, maxSize) == -1) {
            perror("Counldn't read\n");
            return;
        }
        printf("Client: %s", buffer);

        if (strcmp(buffer, "Bye\n") == 0) {
            strcpy(buffer, "Servering closing connection...\n");
            write(sockfd, buffer, maxSize);
            break;
        } else if (strcmp(buffer, "GivemeyourVideo\n") == 0) {
            fp = fopen("sendVid.mp4", "rb");
            if (fp == NULL) {
                printf("Error opening file\n");
                strcpy(buffer, "Error opening video file\n");
                write(sockfd, buffer, maxSize);
                continue;
            } else {
                strcpy(buffer, "Sending file...\n");
                write(sockfd, buffer, maxSize);
                sendVideo(sockfd, buffer, fp);
                printf("Transfer done\n");
                fclose(fp);
            }
        } else {
            strcpy(buffer, "Ok, noted!\n");
            write(sockfd, buffer, maxSize);
        }
    }
}

int main() {
    int sockfd, newSockfd, csize;
    struct sockaddr_in *addr = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in)), cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Couldn't create socket\n");
        return -1;
    }
    printf("Socket created!\n");

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("Socket bind failed\n");
        return -1;
    }
    printf("Socket binded successfully\n");

    if (listen(sockfd, 5) < 0) {
        perror("Failed to listen\n");
        return -1;
    }
    printf("Socket in listening mode\n");
    csize = sizeof(cli);

    newSockfd = accept(sockfd, (struct sockaddr *)&cli, (socklen_t *)&csize);

    if (newSockfd < 0) {
        perror("Counln't accept connection\n");
        return -1;
    }
    printf("Server is connected to a client\n\n");

    chat(newSockfd);
    close(sockfd);

    return 0;
}
