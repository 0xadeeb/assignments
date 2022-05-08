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
    read(sockfd, buffer, maxSize);
    printf("%s", buffer);
}

void createFile(int sockfd) {
    int statusCode;
    char buffer[maxSize], junk;
    scanf("%c", &junk);
    scanf("%[^\n]%*c", buffer);
    write(sockfd, buffer, maxSize);
    read(sockfd, &statusCode, sizeof(int));
    if (statusCode == 201) {
        printf("Text file successfully created\n");
    } else if (statusCode == 401) {
        printf("Test file already exists\n");
    } else {
        printf("Some error occured, please try again\n");
    }
}

void storeFile(int sockfd) {
    int statusCode;
    char buffer[maxSize], fileName[maxSize];
    FILE *fp;
    scanf("%s", fileName);
    if (access(fileName, R_OK) == 0 && (fp = fopen(fileName, "rb"))) {
        statusCode = 202;
        write(sockfd, &statusCode, sizeof(int));
        write(sockfd, fileName, maxSize);
        bzero(buffer, maxSize);
        double end, start;
        start = clock();
        while (fread(buffer, sizeof(char), maxSize, fp) > 0) {
            send(sockfd, buffer, maxSize, 0);
            bzero(buffer, maxSize);
        }
        end = clock();
        bzero(buffer, maxSize);
        strcpy(buffer, "Transfer done\n");
        write(sockfd, buffer, maxSize);
        printf("Transfer of file '%s' done in %.1lf micro seconds\n", fileName,
               (end - start) / CLOCKS_PER_SEC * 1e6);
        fclose(fp);
    } else {
        printf("File not present or doesn't contain read permission\n");
        statusCode = 402;
        write(sockfd, &statusCode, sizeof(int));
    }
}

void getFile(int sockfd) {
    int statusCode;
    char buffer[maxSize], filename[maxSize];
    scanf("%s", filename);
    write(sockfd, filename, maxSize);
    read(sockfd, &statusCode, sizeof(int));
    if (statusCode == 202) {
        FILE *fp = fopen(filename, "wb");
        double end, start;
        start = clock();
        while (recv(sockfd, buffer, maxSize, 0) > 0) {
            if (strcmp(buffer, "Transfer done\n") == 0) {
                printf("done\n");
                break;
            }
            fwrite(buffer, sizeof(char), maxSize, fp);
            bzero(buffer, maxSize);
        }
        end = clock();
        printf("Transfer of file '%s' done in %.1lf micro seconds\n", filename,
               (end - start) / CLOCKS_PER_SEC * 1e6);
        fclose(fp);
    } else {
        printf("Can't open file\n");
    }
}

void communicate(int sockfd) {
    char buffer[maxSize];
    int statusCode;
    while (1) {
        scanf("%s", buffer);
        write(sockfd, buffer, maxSize);
        if (strcmp(buffer, "ListDir") == 0) {
            listDir(sockfd);
        } else if (strcmp(buffer, "CreateFile") == 0) {
            createFile(sockfd);
        } else if (strcmp(buffer, "StoreFile") == 0) {
            storeFile(sockfd);
        } else if (strcmp(buffer, "GetFile") == 0) {
            getFile(sockfd);
        } else if (strcmp(buffer, "QUIT") == 0) {
            break;
        } else if (strcmp(buffer, "USERN") == 0 || strcmp(buffer, "PASSWD") == 0) {
            scanf("%s", buffer);
            printf("User logged in already!\n");
            fflush(stdin);
        } else {
            read(sockfd, &statusCode, sizeof(int));
            printf("Status code not supported, %d\n", statusCode);
            fflush(stdin);
        }
    }
}

bool authenticate(int sockfd) {
    char buffer[maxSize], junk;
    int statusCode;
    scanf("%s", buffer);
    scanf("%c", &junk);
    write(sockfd, buffer, maxSize);
    if (strcmp(buffer, "USERN") == 0) {
        scanf("%s", buffer);
        scanf("%c", &junk);
        write(sockfd, buffer, maxSize);
        read(sockfd, &statusCode, sizeof(int));
        if (statusCode == 301) {
            printf("Incorrect Username\n");
            return false;
        } else if (statusCode == 300) {
            scanf("%s", buffer);
            scanf("%c", &junk);
            write(sockfd, buffer, maxSize);
            if (strcmp(buffer, "PASSWD") == 0) {
                scanf("%[^\n]%*c", buffer);
                write(sockfd, buffer, maxSize);
                read(sockfd, &statusCode, sizeof(int));
                if (statusCode == 310) {
                    printf("Incorrect Passowrd\n");
                    return false;
                } else if (statusCode == 305) {
                    return true;
                }
            } else {
                read(sockfd, &statusCode, sizeof(int));
                printf("Unknown error, %d", statusCode);
                return false;
            }
        } else {
            printf("Unknown error, %d", statusCode);
            return false;
        }
    } else {
        write(sockfd, buffer, maxSize);
        printf("Couldn't authenticate\n");
        return false;
    }
}

int main() {
    int sockfd, statusCode;
    struct sockaddr_in addr;
    char cmd[25];

    scanf("%s", cmd);
    while (strcmp(cmd, "START")) {
        printf("Connection not established\n");
        scanf("%s", cmd);
    }

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

    read(sockfd, &statusCode, sizeof(int));
    if (statusCode == 200)
        printf("OK Connection is set up\n");
    else {
        close(sockfd);
        printf("Unknown error\n");
        return -1;
    }

    if (authenticate(sockfd)) {
        printf("Authenicated\n");
        communicate(sockfd);
    } else {
        close(sockfd);
        return -1;
    }
    close(sockfd);
    return 0;
}
