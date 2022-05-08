#include "socket.h"

void shop(int sockfd, struct sockaddr_in *addr, int len) {
    char buffer[maxSize], junk;
    int count, opt, fruit;
    socklen_t msglen;

    while (1) {
        // Fruits or inventroy
        bzero(buffer, maxSize);
        recvfrom(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, &msglen);
        printf("------Menu------\n%s", buffer);

        scanf("%d", &opt);
        sendto(sockfd, &opt, sizeof(int), 0, (struct sockaddr *)addr, len);

        if (opt == 1) {
            // Which fruit
            bzero(buffer, maxSize);
            recvfrom(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, &msglen);
            printf("\n%s", buffer);

            scanf("%d", &fruit);
            sendto(sockfd, &fruit, sizeof(int), 0, (struct sockaddr *)addr, len);

            // Count of the fruit
            bzero(buffer, maxSize);
            recvfrom(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, &msglen);
            printf("%s", buffer);

            scanf("%d", &count);
            sendto(sockfd, &count, sizeof(int), 0, (struct sockaddr *)addr, len);

            // Success or failure
            bzero(buffer, maxSize);
            recvfrom(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, &msglen);
            printf("%s\n", buffer);
        } else {
            bzero(buffer, maxSize);
            recvfrom(sockfd, buffer, maxSize, 0, (struct sockaddr *)addr, &msglen);
            printf("\nInventory\n%s", buffer);
            break;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char buffer[maxSize] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Can't allocate Socket\n");
        return -1;
    }
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

    strcpy(buffer, "Hello server!\n");
    sendto(sockfd, buffer, maxSize, 0, (struct sockaddr *)&addr, sizeof(addr));

    shop(sockfd, &addr, sizeof(addr));
    close(sockfd);
    return 0;
}
