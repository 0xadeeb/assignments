#include "socket.h"

void shop(int sockfd) {
    char buffer[maxSize], junk;
    int count, opt, fruit;

    while (1) {
        // Fruits or inventroy
        bzero(buffer, maxSize);
        read(sockfd, buffer, maxSize);
        printf("------Menu------\n%s", buffer);

        scanf("%d", &opt);
        write(sockfd, &opt, sizeof(int));

        if (opt == 1) {
            // Which fruit
            bzero(buffer, maxSize);
            read(sockfd, buffer, maxSize);
            printf("\n%s", buffer);

            scanf("%d", &fruit);
            write(sockfd, &fruit, sizeof(int));

            // Count of the fruit
            bzero(buffer, maxSize);
            read(sockfd, buffer, maxSize);
            printf("%s", buffer);

            scanf("%d", &count);
            write(sockfd, &count, sizeof(int));

            // Success or failure
            bzero(buffer, maxSize);
            read(sockfd, buffer, maxSize);
            printf("%s\n", buffer);
        } else {
            bzero(buffer, maxSize);
            read(sockfd, buffer, maxSize);
            printf("\nInventory\n%s", buffer);
            break;
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

    shop(sockfd);
    close(sockfd);
    return 0;
}
