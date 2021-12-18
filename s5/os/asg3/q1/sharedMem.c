#include "sharedMem.h"

static int attachSharedMem(char* filename, int s){
    key_t key = ftok(filename, 0); 
    int shmid = shmget(key, s, 0666 | IPC_CREAT);
    if(shmid == -1){
        perror("shmget");
        return -1;
    }
    return shmid;
}

char* getSharedMem(char* filename, int s){
    int shmid = attachSharedMem(filename, s);
    if(shmid == -1){
        return NULL;
    }
    char* shm = shmat(shmid, NULL, 0);
    if(shm == (char*)-1){
        perror("shmat");
        return NULL;
    }
    return shm;
}

bool detachSharedBlock(char* shm){
    if(shmdt(shm) == -1){
        perror("shmdt");
        return false;
    }
    return true;
}

bool destroySharedBlock(char* filename, int s){
    int shmid = attachSharedMem(filename, s);
    if(shmid == -1){
        return false;
    }
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
        perror("shmctl");
        return false;
    }
    return true;
}

int** getAllptrs(char* block){
    int **ptrs = (int**)malloc(sizeof(int*) * 6);
    for(int i = 0; i < 6; i++){
        ptrs[i] = (int*)block + 10*sizeof(char) + i * sizeof(int);
    }
    return ptrs;
}