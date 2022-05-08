#include <arpa/inet.h>
#include <dirent.h>
#include <netinet/in.h>
#include <pthread.h>
#include <regex.h>
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
#define SMTP_PORT 8080
#define POP_PORT 8088
#define MAX_CHAR 4500

typedef struct cred {
    char username[25], password[25];
} Cred;

typedef struct mail {
    int sno;
    char from[25], to[25], subject[100], body[MAX_CHAR];
    short int min, hour, day, month, year;
    struct mail *next;
} mail;

int send_packet(int sockfd, char *data, int length);
int recv_packet(int sock_fd, char **data);
char *verify_email(char *email, Cred *creds, int n);
bool verify_email_client(char *email);
bool check_username(char *email, char *uname);
bool starts_with(char *text, char *pattern);
