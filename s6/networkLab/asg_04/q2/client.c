#include "socket.h"

void mathfn(int sockfd) {
    char exp[maxSize], buffer[maxSize];
    float res;
    while (1) {
        bzero(buffer, maxSize);
        bzero(exp, maxSize);
        if (!read(sockfd, buffer, maxSize))
            break;
        printf("Server - %s", buffer);
        fgets(exp, maxSize, stdin);
        write(sockfd, exp, maxSize);
        if (strcmp(exp, "Exit\n") == 0)
            break;
        read(sockfd, &res, sizeof(float));
        printf("%s = %.2f\n", exp, res);
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

    mathfn(sockfd);
    close(sockfd);
    return 0;
}
