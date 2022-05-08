#include "socket.h"
#include <wchar.h>

void shop(int sockfd, struct sockaddr_in *addr, int len) {
    int available = 10, fruits[5], count, opt, i;
    socklen_t srvlen = len;
    wmemset(fruits, available, 5);
    char *menu = "1. Buy fruits\n2. Send Inventory\nEnter the option: ",
         *fruitmenu =
             "1. Apple\n2. Mango\n3. Banana\n4. Chikoo\n5 .Papaya\nEnter the fruit needed: ",
         buffer[maxSize];

    while (1) {
        bzero(buffer, maxSize);
        strcpy(buffer, menu);
        sendto(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, len);

        recvfrom(sockfd, &opt, sizeof(int), 0, (struct sockaddr *)addr, &srvlen);

        if (opt == 1) {
            bzero(buffer, maxSize);
            strcpy(buffer, fruitmenu);
            sendto(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, len);

            recvfrom(sockfd, &i, sizeof(int), 0, (struct sockaddr *)addr, &srvlen);
            printf("Fruit: %d\n", i);

            strcpy(buffer, "Enter the number of fruits: ");
            sendto(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, len);
            recvfrom(sockfd, &count, sizeof(int), 0, (struct sockaddr *)addr, &srvlen);

            printf("Count: %d\n", count);

            switch (i) {
            case 1:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                } else {
                    strcpy(buffer, "Not available\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                }
                break;
            case 2:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                } else {
                    strcpy(buffer, "Not available\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                }
                break;
            case 3:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                } else {
                    strcpy(buffer, "Not available\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                }
                break;
            case 4:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                } else {
                    strcpy(buffer, "Not available\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                }
                break;
            case 5:
                if (count >= 0 && count <= fruits[i - 1]) {
                    fruits[i - 1] -= count;
                    strcpy(buffer, "Ok, noted!\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                } else {
                    strcpy(buffer, "Not available\n");
                    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
                }
                break;
            default:
                strcpy(buffer, "Not available\n");
                sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)addr, len);
            }
        } else {
            sprintf(buffer, "Apples: %d\nMangoes: %d\nBananas: %d\nChikoo: %d\nPapaya: %d\n",
                    available - fruits[0], available - fruits[1], available - fruits[2],
                    available - fruits[3], available - fruits[4]);
            sendto(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, len);
            break;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in *addr = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in)), cliaddr;
    socklen_t clilen;
    char buffer[maxSize] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Couldn't create socket\n");
        return -1;
    }
    printf("Socket created!\n");
    bzero(addr, sizeof(struct sockaddr_in));
    bzero(&cliaddr, sizeof(cliaddr));

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("Socket bind failed\n");
        return -1;
    }
    printf("Socket binded successfully\n");

    recvfrom(sockfd, buffer, maxSize, 0, (struct sockaddr *)&cliaddr, &clilen);
    printf("Client: %s\n", buffer);
    shop(sockfd, &cliaddr, sizeof(cliaddr));

    close(sockfd);

    return 0;
}
