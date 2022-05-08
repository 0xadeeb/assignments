#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

mail *getmailList(char *username) {
    char mailBox[25];
    sprintf(mailBox, "%s/mymailbox.txt", username);
    FILE *mb = fopen(mailBox, "r");
    char line[100];
    mail *head = NULL, *cur = NULL, *prev;
    int i = 1;
    while (mb && fscanf(mb, "%[^\n]%*c", line) != EOF) {
        if (!strlen(line) || line[0] == '\n') {
            continue;
        } else if (starts_with(line, "^From")) {
            prev = cur;
            cur = (mail *)malloc(sizeof(mail));
            cur->sno = i++;
            if (!head) {
                head = cur;
            } else {
                prev->next = cur;
            }
            strcpy(cur->from, line + 6);
            bzero(cur->body, MAX_CHAR);
        } else if (starts_with(line, "^To")) {
            strcpy(cur->to, line + 4);
        } else if (starts_with(line, "^Subject")) {
            strcpy(cur->subject, line + 9);
        } else if (starts_with(line, "^Recieved")) {
            sscanf(line + 10, "%hd-%hd-%hd, %hd:%hd%*c", &cur->day, &cur->month, &cur->year,
                   &cur->hour, &cur->min);
        } else {
            sprintf(cur->body, "%s%s\n", cur->body, line);
        }
        if (i == 0) {
            printf("%s\n", line);
        }
    }
    if (cur)
        cur->next = NULL;
    fclose(mb);
    return head;
}

void delList(mail *head) {
    mail *t = head;
    while (t) {
        t = t->next;
        free(head);
        head = t;
    }
}

void deleteMail(mail **head, int sno) {
    mail *t, *cur = *head;
    if (sno == 1) {
        *head = cur->next;
        free(cur);
    } else {
        for (int i = 1; cur; i++, cur = cur->next) {
            if (i == sno - 1) {
                t = cur->next;
                cur->next = t->next;
                free(t);
                break;
            }
        }
    }
}

void sendDetails(mail *head, int sno, int sockfd) {
    char buffer[MAX_CHAR];
    mail *t = head;
    for (int i = 1; t; i++, t = t->next) {
        if (i == sno) {
            bzero(buffer, MAX_CHAR);
            sprintf(buffer, "%sSno: %d\n", buffer, t->sno);
            sprintf(buffer, "%sFrom: %s\n", buffer, t->from);
            sprintf(buffer, "%sTo: %s\n", buffer, t->to);
            sprintf(buffer, "%sSubject: %s\n", buffer, t->subject);
            sprintf(buffer, "%sRecieved: %hd-%hd-%hd, %hd:%hd\n", buffer, t->day, t->month, t->year,
                    t->hour, t->min);
            sprintf(buffer, "%sBody:%s\n", buffer, t->body);
            send_packet(sockfd, buffer, MAX_CHAR);
        }
    }
}

void writeTofile(mail *head, char *username) {
    char mailBox[25];
    sprintf(mailBox, "%s/mymailbox.txt", username);
    FILE *mb = fopen(mailBox, "w");

    for (mail *t = head; t; t = t->next) {
        fprintf(mb, "From: %s\n", t->from);
        fprintf(mb, "To: %s\n", t->to);
        fprintf(mb, "Subject: %s\n", t->subject);
        fprintf(mb, "Recieved: %d-%d-%d, %d:%d\n", t->day, t->month, t->year, t->hour, t->min);
        fprintf(mb, "%s", t->body);
    }
    fclose(mb);
}

void printMails(mail *head) {
    mail *t = head;
    while (t) {
        printf("sno: %d\n", t->sno);
        printf("from: %s\n", t->from);
        printf("to: %s\n", t->to);
        printf("subject: %s\n", t->subject);
        printf("recieved: %hd-%hd-%hd, %hd:%hd\n", t->day, t->month, t->year, t->hour, t->min);
        printf("body:%s\n", t->body);
        t = t->next;
    }
}

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

    if (strcmp(buffer, "Authenticated\n") == 0) {
        while (1) {
            int o;
            read(sockfd, &o, sizeof(int));
            if (o == 2 || o == 3) {
                strcpy(buffer, "Good bye\n");
                write(sockfd, buffer, maxSize);
                break;
            }
            mail *head, *cur;
            head = getmailList(username);
            // printMails(head);
            bzero(buffer, maxSize);
            cur = head;
            if (!head) {
                strcpy(buffer, "No mail in mailbox!\n");
                send_packet(sockfd, buffer, maxSize);
                continue;
            }
            while (cur) {
                sprintf(buffer, "%s%d | %s\t| %hd-%hd-%hd, %hd:%hd | %s\n", buffer, cur->sno,
                        cur->from, cur->day, cur->month, cur->year, cur->hour, cur->min,
                        cur->subject);
                cur = cur->next;
            }
            send_packet(sockfd, buffer, maxSize);
            int sno;
            char opt;
            read(sockfd, &opt, sizeof(char));
            read(sockfd, &sno, sizeof(int));
            if (opt == 'd') {
                deleteMail(&head, sno);
                writeTofile(head, username);
                delList(head);
                strcpy(buffer, "Mail deleted successfully\n");
                write(sockfd, buffer, maxSize);
            } else if (opt == 'q') {
                delList(head);
                strcpy(buffer, "Good bye\n");
                write(sockfd, buffer, maxSize);
                break;
            } else if (opt == 'd') {
                sendDetails(head, sno, sockfd);
                delList(head);
            } else if (opt == 'f') {
                recv_packet(sockfd, &data);
                bool found = false;
                for (int i = 0; i < no_of_users; i++) {
                    if (strcmp(creds[i].username, data) == 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    strcpy(buffer, "INVALID MAIL-ID\n");
                } else {

                    bzero(buffer, maxSize);
                    mail *t = head;
                    while (t) {
                        if (check_username(t->from, data)) {
                            sprintf(buffer, "%sFrom: %s\n", buffer, t->from);
                            sprintf(buffer, "%sTo: %s\n", buffer, t->to);
                            sprintf(buffer, "%sSubject: %s\n", buffer, t->subject);
                            sprintf(buffer, "%sRecieved: %hd-%hd-%hd, %hd:%hd\n", buffer, t->day,
                                    t->month, t->year, t->hour, t->min);
                            sprintf(buffer, "%sBody:\n%s\n", buffer, t->body);
                        }
                        t = t->next;
                    }
                    if (strlen(buffer) == 0) {
                        strcpy(buffer, "NO MAILS TO SHOW\n");
                    }
                }
                send_packet(sockfd, buffer, sizeof(buffer));
            }
        }
    }
    return NULL;
}

void helper() {
    printf("Help:\n");
    printf("Run ~./pserver <port_no>~\n");
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
