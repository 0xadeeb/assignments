#include "socket.h"

void revData(int sockfd) {
    char buffer[maxSize];
    int Sn = 0, n = 50, i, k;
    while (i < n) {
        bzero(buffer, maxSize);
        if ((k = read(sockfd, buffer, maxSize)) < 0)
            perror("Error reading\n");
        if (k > 0 && buffer[0] == Sn + 48) {
            printf("Recieved with msg: %s", buffer + 1);
            bzero(buffer, maxSize);
            Sn = Sn ^ 1;
            buffer[0] = Sn + 48;
            write(sockfd, buffer, maxSize);
            i++;
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

    revData(sockfd);
    printf("done\n");
    close(sockfd);
    return 0;
}
