#include <arpa/inet.h>
#include <dirent.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define maxSize 512
#define port 4035

void listDir(int sockfd) {
    char buffer[maxSize];
    DIR *d = opendir(".");
    struct dirent *dir;
    bzero(buffer, maxSize);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                sprintf(buffer, "%s%s\n", buffer, dir->d_name);
            }
        }
    }
    write(sockfd, buffer, maxSize);
}

void createFile(int sockfd) {
    int statusCode;
    char buffer[maxSize];
    DIR *d = opendir(".");
    struct dirent *dir;
    read(sockfd, buffer, maxSize);
    sprintf(buffer, "%s.txt", buffer);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(buffer, dir->d_name) == 0) {
                statusCode = 401;
                write(sockfd, &statusCode, sizeof(int));
                return;
            }
        }
        FILE *fp = fopen(buffer, "w");
        fclose(fp);
        statusCode = 201;
        write(sockfd, &statusCode, sizeof(int));
        return;
    }
    statusCode = 405;
    write(sockfd, &statusCode, sizeof(int));
}

void storeFile(int sockfd) {
    int statusCode;
    char buffer[maxSize], filename[maxSize];
    read(sockfd, &statusCode, sizeof(int));
    if (statusCode == 202) {
        read(sockfd, filename, maxSize);
        FILE *fp = fopen(filename, "wb");
        int i = 0;
        while (recv(sockfd, buffer, maxSize, 0) > 0) {
            if (strcmp(buffer, "Transfer done\n") == 0) {
                printf("Done\n");
                break;
            }
            fwrite(buffer, sizeof(char), maxSize, fp);
            bzero(buffer, maxSize);
        }
        fclose(fp);
    }
}

void getFile(int sockfd) {
    int statusCode;
    char buffer[maxSize], filename[maxSize];
    FILE *fp;
    read(sockfd, filename, maxSize);
    if (access(filename, R_OK) == 0 && (fp = fopen(filename, "rb"))) {
        statusCode = 202;
        write(sockfd, &statusCode, sizeof(int));
        bzero(buffer, maxSize);
        while (fread(buffer, sizeof(char), maxSize, fp) > 0) {
            send(sockfd, buffer, maxSize, 0);
            bzero(buffer, maxSize);
        }
        strcpy(buffer, "Transfer done\n");
        write(sockfd, buffer, maxSize);
        fclose(fp);
    } else {
        statusCode = 402;
        write(sockfd, &statusCode, sizeof(int));
    }
}

void communicate(int sockfd) {
    char buffer[maxSize], parameters[maxSize];
    int statusCode;
    while (1) {
        read(sockfd, buffer, maxSize);
        if (strcmp(buffer, "ListDir") == 0) {
            listDir(sockfd);
        } else if (strcmp(buffer, "CreateFile") == 0) {
            createFile(sockfd);
        } else if (strcmp(buffer, "StoreFile") == 0) {
            // printf("Todo\n");
            storeFile(sockfd);
        } else if (strcmp(buffer, "GetFile") == 0) {
            // printf("Todo\n");
            getFile(sockfd);
        } else if (strcmp(buffer, "QUIT") == 0) {
            break;
        } else if (strcmp(buffer, "USERN") == 0 || strcmp(buffer, "PASSWD") == 0) {
            scanf("%s", buffer);
            printf("User logged in already!\n");
        } else {
            statusCode = 505;
            write(sockfd, &statusCode, sizeof(int));
            printf("Status code not supported, %d\n", statusCode);
            fflush(stdin);
        }
    }
}

bool authenticate(int sockfd) {
    int statusCode = 301;
    char buffer[maxSize];
    read(sockfd, buffer, maxSize);

    if (strcmp(buffer, "USERN") == 0) {
        read(sockfd, buffer, maxSize);
        FILE *fp = fopen("../logincred.txt", "r");
        if (fp == NULL) {
            printf("Unknown error\n");
            return false;
        }
        bool found = false;
        char username[25], password[25];
        while (fscanf(fp, "%[^,]s", username) == 1) {
            fgetc(fp);
            fscanf(fp, "%s", password);
            fgetc(fp);
            if (strcmp(buffer, username) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            statusCode = 301;
            write(sockfd, &statusCode, sizeof(int));
            return false;
        }
        statusCode = 300;
        write(sockfd, &statusCode, sizeof(int));
        read(sockfd, buffer, maxSize);

        if (strcmp(buffer, "PASSWD") == 0) {
            read(sockfd, buffer, maxSize);
            if (strcmp(buffer, password) == 0) {
                statusCode = 305;
                write(sockfd, &statusCode, sizeof(int));
                return true;
            } else {
                statusCode = 310;
                write(sockfd, &statusCode, sizeof(int));
                return false;
            }
        } else {
            statusCode = 505;
            write(sockfd, &statusCode, sizeof(int));
            printf("Unknown error, %d", statusCode);
            return false;
        }

    } else {
        statusCode = 505;
        write(sockfd, &statusCode, sizeof(int));
        return false;
    }

    return true;
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
    int statusCode = 200;
    write(newSockfd, &statusCode, sizeof(int));

    if (authenticate(newSockfd) == true) {
        communicate(newSockfd);
    }
    close(sockfd);

    return 0;
}
