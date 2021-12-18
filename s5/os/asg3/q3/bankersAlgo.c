#include "q3.h" 

void dealloc(int* availabe, int *allocated, int r){
    int i;
    for(i = 0; i < r; i++){
        availabe[i] = availabe[i] + allocated[i];
    }
}

bool canAllocate(int* required, int* available, int r){
    int i;
    for(i = 0; i < r; i++){
        if(required[i] > available[i]){
            return false;
        }
    }
    return true;
}

bool findSafeSeq(int *available, int **allocated, int **required, int p, int r, bool* set, int* seq, int i){
    if(i == p){
        return true;
    }

    for(int j = 0; j < p; j++){
        if(!set[j] && canAllocate(required[j], available, r)){
            set[j] = true;
            seq[i] = j;
            dealloc(available, allocated[j], r);
            return findSafeSeq(available, allocated, required, p, r, set, seq, i + 1);
        }
    }

    return false;

}