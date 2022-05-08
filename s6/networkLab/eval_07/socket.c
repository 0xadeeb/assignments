#include "socket.h"
#include <regex.h>
#include <string.h>

#define HEADER_SIZE 8

int send_packet(int sockfd, char *data, int length) {
    char header[HEADER_SIZE];
    char format[20];

    sprintf(format, "%%0%dd", HEADER_SIZE - 1);
    sprintf(header, format, length);

    header[HEADER_SIZE - 1] = 0;

    send(sockfd, header, HEADER_SIZE, 0);

    return send(sockfd, data, length, 0);
}

int recv_packet(int sock_fd, char **data) {
    char header[HEADER_SIZE];

    recv(sock_fd, header, HEADER_SIZE, 0);

    int length = -1;

    sscanf(header, "%d", &length);

    if (length <= 0) {
        printf("Invalid header format\n");
        return -1;
    }

    char *buffer = calloc(length, sizeof(char));
    *data = buffer;

    int recv_len = recv(sock_fd, buffer, length, 0);
    buffer[recv_len] = '\0';
    return recv_len + 1;
}

bool verify_email_client(char *email) {
    regex_t regex;
    int rti;
    char *exp = "^([[:graph:]]+)@([[:graph:]]+)$";
    regcomp(&regex, exp, REG_EXTENDED);
    rti = regexec(&regex, email, 0, NULL, 0);
    if (!rti) {
        return true;
    } else {
        return false;
    }
    regfree(&regex);
}

char *verify_email(char *email, Cred *creds, int n) {
    regex_t regex;
    regmatch_t pmatch[3];
    int rti;
    char *exp = "^([[:graph:]]+)@([[:graph:]]+)$", *username = (char *)malloc(25 * sizeof(char));
    regcomp(&regex, exp, REG_EXTENDED);
    rti = regexec(&regex, email, 3, pmatch, 0);
    if (!rti) {
        for (int i = pmatch[1].rm_so; i < pmatch[1].rm_eo; i++) {
            // printf("%c", email[i]);
            username[i - pmatch[1].rm_so] = email[i];
        }
        // printf("\n");
        username[pmatch[1].rm_eo] = 0;
        /* for (int i = pmatch[2].rm_so; i < pmatch[2].rm_eo; i++) { */
        /*     printf("%c", email[i]); */
        /* } */
        /* printf("\n"); */
        for (int i = 0; i < n; i++) {
            if (strcmp(creds[i].username, username) == 0) {
                return username;
            }
        }
        return NULL;

    } else {
        return NULL;
    }
    regfree(&regex);
}

bool check_username(char *email, char *uname) {
    regex_t regex;
    regmatch_t pmatch[2];
    int rti;
    char *exp = "^([[:graph:]]+)@[[:graph:]]+$", username[25];
    regcomp(&regex, exp, REG_EXTENDED);
    rti = regexec(&regex, email, 2, pmatch, 0);
    if (!rti) {
        for (int i = pmatch[1].rm_so; i < pmatch[1].rm_eo; i++) {
            username[i - pmatch[1].rm_so] = email[i];
        }
        username[pmatch[1].rm_eo] = 0;
        if (strcmp(username, uname) == 0) {
            return true;
        } else
            return NULL;

    } else {
        return false;
    }
    regfree(&regex);
}

bool starts_with(char *text, char *pattern) {
    regex_t regex;
    int rti;
    regcomp(&regex, pattern, REG_EXTENDED);
    rti = regexec(&regex, text, 0, NULL, 0);
    if (!rti) {
        return true;
    } else {
        return false;
    }
    regfree(&regex);
}
