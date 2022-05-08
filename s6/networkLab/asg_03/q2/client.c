#include "socket.h"

void recieveVideo(int sockfd, char *buffer, FILE *fp) {
    bzero(buffer, maxSize);
    while (recv(sockfd, buffer, maxSize, 0) > 0) {
        if (strcmp(buffer, "Transfer done\n") == 0) {
            break;
        }
        fwrite(buffer, sizeof(char), maxSize, fp);
        bzero(buffer, maxSize);
    }
}

void chat(int sockfd) {
    char buffer[maxSize];
    FILE *fp;

    while (1) {
        bzero(buffer, maxSize);
        printf("Type text to send to server: ");
        fgets(buffer, maxSize, stdin);
        write(sockfd, buffer, maxSize);
        if (strcmp(buffer, "Bye\n") == 0) {
            read(sockfd, buffer, maxSize);
            printf("Server: %s\n", buffer);
            return;
        } else if (strcmp(buffer, "GivemeyourVideo\n") == 0) {
            read(sockfd, buffer, maxSize);
            printf("Server: %s", buffer);
            fp = fopen("revfile.mp4", "wb");
            if (fp == NULL || !strcmp(buffer, "Error opening video file\n")) {
                printf("Error opening file\n");
                continue;
            } else {
                recieveVideo(sockfd, buffer, fp);
                printf("Recieve done\n");
                fclose(fp);
            }
        } else {
            read(sockfd, buffer, maxSize);
            printf("Server: %s\n", buffer);
        }
    }
}

int main() {
    int sockfd, newSockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Can't allocate Socket\n");
        return -1;
    }
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("Counldn't connect to the server\n");
        return -1;
    }

    printf("Connected to the server successfully\n");

    chat(sockfd);
    close(sockfd);
    return 0;
}
