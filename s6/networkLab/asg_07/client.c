#include "socket.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

void handleClient(int ssockfd, int psockfd) {
    char username[25], password[25], *buffer, data[maxSize];
    printf("Email Id: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    send_packet(ssockfd, username, sizeof(username));
    send_packet(ssockfd, password, sizeof(password));

    recv_packet(ssockfd, &buffer);
    printf("SMTP server: %s\n", buffer);

    send_packet(psockfd, username, sizeof(username));
    send_packet(psockfd, password, sizeof(password));

    recv_packet(psockfd, &buffer);
    printf("Pop server: %s\n", buffer);
    bool popend = false;

    if (strcmp(buffer, "Authenticated\n") == 0) {
        while (1) {
            int opt;
            if (!popend)
                printf("1. Manage Mail\n2. Send mail\n3. EXIT\n");
            else
                printf("1. Send mail\n2. EXIT\n");
            printf("Enter the option\n");
            scanf("%d", &opt);
            if (popend)
                opt++;
            if (opt == 1) {
                write(psockfd, &opt, sizeof(int));
                recv_packet(psockfd, &buffer);
                printf("%s\n", buffer);
                if (strcmp(buffer, "No mail in mailBox!\n") == 0) {
                    continue;
                }
                char opt1, junk;
                int sno;
                printf("'d' to delete a mail\n");
                printf("'q' to exit\n");
                printf("Any other key to view the condents of the mail\n");
                scanf("%c", &junk);
                printf("Enter: ");
                scanf("%c", &opt1);
                printf("Enter sno: ");
                scanf("%d", &sno);
                write(psockfd, &opt1, sizeof(char));
                write(psockfd, &sno, sizeof(int));
                if (opt1 == 'q') {
                    read(psockfd, data, maxSize);
                    printf("Pop server: %s", data);
                    popend = true;
                } else if (opt1 == 'd') {
                    read(psockfd, data, maxSize);
                    printf("%s", data);
                } else {
                    recv_packet(psockfd, &buffer);
                    printf("%s", buffer);
                }

            } else if (opt == 2) {
                char to[50], from[50], subject[100], body[MAX_CHAR], junk, buffer[maxSize];
                scanf("%c", &junk);
                printf("From: ");
                scanf("%[^\n]%*c", from);
                printf("To: ");
                scanf("%[^\n]%*c", to);
                printf("Subject: ");
                scanf("%[^\n]%*c", subject);
                printf("Message body:\n");
                bzero(body, MAX_CHAR);
                do {
                    scanf("%[^\n]%*c", buffer);
                    sprintf(body, "%s%s\n", body, buffer);
                } while (strcmp(buffer, ".") != 0);
                if (!strlen(from) || !strlen(to) || !strlen(subject) ||
                    !verify_email_client(from) || !verify_email_client(to) ||
                    !check_username(from, username)) {
                    printf("Incorrect format\n");
                    continue;
                }
                write(ssockfd, &opt, sizeof(int));

                send_packet(ssockfd, from, sizeof(from));
                send_packet(ssockfd, to, sizeof(to));
                send_packet(ssockfd, subject, sizeof(subject));
                send_packet(ssockfd, body, sizeof(body));

                read(ssockfd, buffer, maxSize);
                printf("%s\n", buffer);
            } else if (opt == 3) {
                write(ssockfd, &opt, sizeof(int));
                read(ssockfd, data, maxSize);
                printf("SMTP server: %s", data);
                if (!popend) {
                    write(psockfd, &opt, sizeof(int));
                    read(psockfd, data, maxSize);
                    printf("POP server: %s", data);
                }
                break;
            }
        }
    }

    return;
}

int main(int argc, char **argv) {
    int pport = POP_PORT, sport = SMTP_PORT;
    int ssockfd, psockfd;
    struct sockaddr_in saddr, paddr;

    ssockfd = socket(AF_INET, SOCK_STREAM, 0);
    psockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (ssockfd < 0 || psockfd < 0) {
        perror("Can't allocate Socket\n");
        return -1;
    }
    bzero(&saddr, sizeof(saddr));
    bzero(&paddr, sizeof(paddr));

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(sport);

    paddr.sin_family = AF_INET;
    paddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    paddr.sin_port = htons(pport);

    if (connect(ssockfd, (struct sockaddr *)&saddr, sizeof(saddr))) {
        perror("Counldn't connect to SMTP server\n");
        return -1;
    }
    if (connect(psockfd, (struct sockaddr *)&paddr, sizeof(paddr))) {
        perror("Counldn't connect to POP server\n");
        return -1;
    }
    printf("Successfully connected to SMTP and POP servers\n");
    handleClient(ssockfd, psockfd);
    close(ssockfd);
    close(psockfd);
    return 0;
}
