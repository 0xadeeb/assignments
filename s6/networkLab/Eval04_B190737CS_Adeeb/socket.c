#include "socket.h"
#include <stdio.h>
#include <stdlib.h>

void error(int n, char *str) {
    if (n < 0) {
        perror(str);
        exit(1);
    }
}
