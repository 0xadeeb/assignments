#include "sharedMem.h"

void main(){

    char* block = getSharedMem(fname, size);

    char* password = block;
    int** ptr = getAllptrs(block);

    for(int i = 0; i < 6; i++){
        *(ptr[i]) = 0; 
    }

    do{
        printf("Enter a password of length 10\n");
        scanf("%s", password);

    }while(strlen(password) != 10);
    
    *(ptr[0]) = 1;

    do{
        sleep(1);
    }while(*(ptr[2]) == 0);

    if(*(ptr[5]) == 0) printf("Password is weak\n");
    else printf("Password is strong\n");

    detachSharedBlock(block);
    destroySharedBlock(fname, size);
}