#include "socket.h"
#include <wchar.h>

void shop(int sockfd) {
    int available = 10, fruits[5], count, opt, i;
    wmemset(fruits, available, 5);
    char *menu = "1. Buy fruits\n2. Send Inventory\nEnter the option: ",
         *fruitmenu =
             "1. Apple\n2. Mango\n3. Banana\n4. Chikoo\n5 .Papaya\nEnter the fruit needed: ",
         buffer[maxSize];

    while (1) {
        bzero(buffer, maxSize);
        strcpy(buffer, menu);
        write(sockfd, buffer, maxSize);

        read(sockfd, &opt, sizeof(int));

        if (opt == 1) {
            bzero(buffer, maxSize);
            strcpy(buffer, fruitmenu);
            write(sockfd, buffer, maxSize);

            read(sockfd, &i, sizeof(int));
            printf("Fruit: %d\n", i);

            strcpy(buffer, "Enter the number of fruits: ");
            write(sockfd, buffer, maxSize);
            read(sockfd, &count, sizeof(int));

            printf("Count: %d\n", count);

            switch (i) {
            case 1:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    write(sockfd, buffer, sizeof(buffer));
                } else {
                    strcpy(buffer, "Not available\n");
                    write(sockfd, buffer, sizeof(buffer));
                }
                break;
            case 2:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    write(sockfd, buffer, sizeof(buffer));
                } else {
                    strcpy(buffer, "Not available\n");
                    write(sockfd, buffer, sizeof(buffer));
                }
                break;
            case 3:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    write(sockfd, buffer, sizeof(buffer));
                } else {
                    strcpy(buffer, "Not available\n");
                    write(sockfd, buffer, sizeof(buffer));
                }
                break;
            case 4:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    write(sockfd, buffer, sizeof(buffer));
                } else {
                    strcpy(buffer, "Not available\n");
                    write(sockfd, buffer, sizeof(buffer));
                }
                break;
            case 5:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    write(sockfd, buffer, sizeof(buffer));
                } else {
                    strcpy(buffer, "Not available\n");
                    write(sockfd, buffer, sizeof(buffer));
                }
                break;
            default:
                strcpy(buffer, "Not available\n");
                write(sockfd, buffer, sizeof(buffer));
            }
        } else {
            sprintf(buffer, "Apples: %d\nMangoes: %d\nBananas: %d\nChikoo: %d\nPapaya: %d\n",
                    available - fruits[0], available - fruits[1], available - fruits[2],
                    available - fruits[3], available - fruits[4]);
            write(sockfd, buffer, maxSize);
            break;
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
    printf("Server is connected to a client\n");

    shop(newSockfd);
    close(sockfd);

    return 0;
}
