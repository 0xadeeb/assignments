#include "sharedMem.h"

void main(){
    char* passowrd = getSharedMem(fname, size);
    int** ptr = getAllptrs(passowrd);

    do{
        sleep(1);
    }while(*(ptr[0]) == 0);

    for(int i = 0; i < 10; i++){
        if(isalnum(passowrd[i]))
            *(ptr[3]) = *(ptr[3]) + 1;
        else
            *(ptr[4]) = *(ptr[4]) + 1;
    }
    
    *(ptr[1]) = 1;

    detachSharedBlock(passowrd);

}