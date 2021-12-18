#include "sharedMem.h"

void main()
{
    char* password = getSharedMem(fname, size);
    int** ptr = getAllptrs(password);

    do{
        sleep(1);
    }while(*(ptr[1]) == 0);

    if(*(ptr[3]) < *(ptr[4]))
        *(ptr[5]) = 1;

    *(ptr[2]) = 1;

    detachSharedBlock(password);

}