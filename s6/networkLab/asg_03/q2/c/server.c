#include "socket.h"

struct timeval timeout;

Frame **createFrames(int n) {
    int Sn = 0;
    Frame **frames = (Frame **)malloc(n * sizeof(Frame *));
    for (int i = 0; i < n; i++) {
        frames[i] = (Frame *)malloc(sizeof(Frame));
        frames[i]->seqNo = Sn;
        Sn = Sn ^ 1;
        frames[i]->kind = seq;
        sprintf(frames[i]->data, "Random msg: %d\n", i + 1);
    }
    return frames;
}

void transferPackets(int sockfd) {
    int Sn = 0, i = 0, n = 50, k;
    Frame **frames = createFrames(n), *frame;
    char buffer[maxSize];
    long start, end, rtt;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
        perror("setsockopt(SO_RCVTIMEO) failed");
    while (i < n) {
        frame = frames[i];
        bzero(buffer, maxSize);
        sprintf(buffer, "%d%s\n", frame->seqNo, frame->data);
        start = clock();
        if (write(sockfd, buffer, maxSize) < 0)
            perror("error sending\n");
        bzero(buffer, maxSize);
        k = read(sockfd, buffer, maxSize);
        end = clock();
        if (k > 0 && buffer[0] - 48 == (Sn ^ 1)) {
            printf("Rtt for frame %d is : %.2lf micro seconds\n", i,
                   10e6 * ((double)end - (double)start) / (double)CLOCKS_PER_SEC);
            Sn = Sn ^ 1;
            i++;
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

    transferPackets(newSockfd);
    printf("done\n");
    close(sockfd);

    return 0;
}
