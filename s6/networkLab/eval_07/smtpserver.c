#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

void *handleClient(void *arg) {

    printf("- New client connected!\n");
    int sockfd = *(int *)arg;
    char *username, *password, fusername[50], fpassword[50], buffer[maxSize], *data, *to_username;

    FILE *cred_file = fopen("logincred.txt", "r");

    int no_of_users = 3;
    Cred *creds = calloc(no_of_users, sizeof(Cred));
    for (int i = 0; fscanf(cred_file, "%s %s", fusername, fpassword) != EOF; i++) {
        strcpy(creds[i].username, fusername);
        strcpy(creds[i].password, fpassword);
    }

    if (recv_packet(sockfd, &username) == -1) {
        printf("! received data was corrupted\n");
        printf("- Closing connection\n");
        close(sockfd);
        return NULL;
    }
    if (recv_packet(sockfd, &password) == -1) {
        printf("! received data was corrupted\n");
        printf("- Closing connection\n");
        close(sockfd);
        return NULL;
    }

    bool found = false;
    for (int i = 0; i < no_of_users; i++) {
        if (strcmp(username, creds[i].username) == 0 && strcmp(password, creds[i].password) == 0) {
            found = true;
            break;
        }
    }
    if (!found) {
        strcpy(buffer, "Wrong login credentials, try again later\n");
        send_packet(sockfd, buffer, strlen(buffer));
        close(sockfd);
        return NULL;
    }
    strcpy(buffer, "Authenticated\n");
    send_packet(sockfd, buffer, strlen(buffer));
    char *from, *to, *subject, *body;
    while (1) {
        int opt;
        read(sockfd, &opt, sizeof(int));

        if (opt == 2) {
            recv_packet(sockfd, &from);
            recv_packet(sockfd, &to);
            recv_packet(sockfd, &subject);
            recv_packet(sockfd, &body);

            if ((to_username = verify_email(to, creds, no_of_users)) == NULL) {
                printf("To: %s\n", to_username);
                strcpy(buffer, "Recipeint not found, email not sent\n");
                write(sockfd, buffer, maxSize);
                goto freevars;
            }
            char mailBox[25] = {0};
            time_t now;
            time(&now);
            struct tm *local = localtime(&now);
            sprintf(mailBox, "%s/mymailbox.txt", to_username);
            free(to_username);
            FILE *mb = fopen(mailBox, "a");
            fprintf(mb, "From: %s\n", from);
            fprintf(mb, "To: %s\n", to);
            fprintf(mb, "Subject: %s\n", subject);
            fprintf(mb, "Recieved: %d-%d-%d, %d:%d\n", local->tm_mday, local->tm_mon + 1,
                    local->tm_year + 1900, local->tm_hour, local->tm_min);
            fprintf(mb, "%s", body);
            fclose(mb);
            strcpy(buffer, "Mail Sent successfully\n");
            write(sockfd, buffer, maxSize);
        freevars:
            free(from);
            free(to);
            free(subject);
            free(body);
        } else if (opt == 3) {
            break;
        }
    }
    close(sockfd);
    return NULL;
}

void helper() {
    printf("Help:\n");
    printf("Run ~./sserver <port_no>~\n");
    printf("port_no is the port number SMRT server will run in\n");
}

int main(int argc, char **argv) {
    int port;
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            helper();
            return 0;
        }
        if (sscanf(argv[1], "%d", &port) != 1) {
            printf("Invalid PORT number\n");
            helper();
            return -1;
        }
    } else {
        printf("Invalid arguments\n");
        helper();
        return -1;
    }

    int sockfd, newSockfd, csize = sizeof(struct sockaddr_in);
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

    while (1) {
        if ((newSockfd = accept(sockfd, (struct sockaddr *)&addr, (socklen_t *)&csize)) < 0) {
            printf("Error accepting connection!");
            continue;
        }

        fflush(stdout);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handleClient, &newSockfd);
    }

    return 0;
}
