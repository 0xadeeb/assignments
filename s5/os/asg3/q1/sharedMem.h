#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include <stdbool.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define size 4096
#define fname "p1.c"

static int attachSharedMem(char* filename, int s);
char* getSharedMem(char* filename, int s);
bool detachSharedBlock(char* shm);
bool destroySharedBlock(char* filename, int s); 
int** getAllptrs(char* block);

#endif