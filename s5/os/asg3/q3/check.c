#include "q3.h"

bool checkReqSeq(int* available, int r){

    int request;
    printf("\nEnter the request sequence: ");

    for(int i = 0; i < r; i++){
        scanf("%d", &request);
        if(request > available[i]){
            for(int j = i+1; j < r; j++){
                int junk;
                scanf("%d", &junk);
            }
            printf("\nRequest %d for process %d is not possible.\n", request, i);
            return false; 
        }
    }
    
    return true;

}

bool checkProcessSeq(int* total, int** allocation, int** required, int p, int r){

    int process;
    bool* allocated = (bool*)calloc(p , sizeof(bool));
    int *available = (int*)malloc(r * sizeof(int));
    memcpy(available, total, sizeof(int) * r);

    printf("\nEnter the process sequence: ");

    for(int i = 0; i < p; i++){
        scanf("%d", &process);
        if(process >= p){
            free(allocated);
            free(available);
            for(int j = i+1; j < p; j++){
                int junk;
                scanf("%d", &junk); 
            }
            printf("\nInvalid process number %d.\n", process);
            return false; 
        }
        if(allocated[process]){
            for(int j = i + 1; j < p; j++){
                int junk;
                scanf("%d", &junk); 
            }
            printf("\nProcess %d has already been allocated.\n", process);
            free(allocated);
            free(available);
            return false; 
        }
        for(int j = 0; j < r; j++){
            if(required[process][j] > available[j]){
                for(i = i+1; i < p; i++){
                    int junk;
                    scanf("%d", &junk); 
                }
                printf("\nNot enough resources to allocate process %d.\n", process);
                free(allocated);
                free(available);
                return false; 
            }
        }

        for(int k = 0; k < r; k++){
            available[k] += allocation[process][k];
        }
        allocated[process] = true; 
    }
    
    free(allocated);
    free(available);
    return true;

}