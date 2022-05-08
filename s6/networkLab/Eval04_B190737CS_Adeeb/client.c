#include "socket.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

void *recvMsg(void *sock) {
    int sockfd = *((int *)sock), len;
    char buffer[maxSize];

    while (1) {
        bzero(buffer, maxSize);
        if ((len = read(sockfd, buffer, maxSize)) <= 0)
            break;
        printf("%s", buffer);
    }

    return NULL;
}

int main() {
    int sockfd, newSockfd;
    struct sockaddr_in addr;
    pthread_t t1;

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
    char buffer[maxSize], junk;
    int authenticated;

    printf("Enter username: ");
    scanf("%[^\n]%*c", buffer);
    write(sockfd, buffer, maxSize);
    printf("Enter the password\n");
    scanf("%[^\n]%*c", buffer);
    write(sockfd, buffer, maxSize);
    read(sockfd, &authenticated, sizeof(int));
    if (authenticated == 0) {
        printf("Wrong password authentication failled!\n");
        close(sockfd);
        return 0;
    }
    bzero(buffer, maxSize);
    read(sockfd, buffer, maxSize);
    printf("%s", buffer);

    pthread_create(&t1, NULL, &recvMsg, &sockfd);

    while (1) {
        bzero(buffer, maxSize);
        fgets(buffer, maxSize, stdin);
        write(sockfd, buffer, maxSize);
        if (strcmp(buffer, "Bye\n") == 0)
            break;
    }

    close(sockfd);
    return 0;
}
