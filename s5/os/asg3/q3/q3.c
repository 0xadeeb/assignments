#include "q3.h"

void printSeq(int* seq, int n){

    printf("\nSafe Sequence: ");
    for(int i = 0; i < n; i++){
        printf("%d ", seq[i]);
    }
    printf("\n");
}

void main(){

    int p, r, *available, *total, **max, **allocation, **required;
    char option;
    int *safeSeq = (int *)calloc(p , sizeof(int));
    bool deadlock = false, checked = false;

    printf("Enter the number of processes: ");
    scanf("%d", &p);
    printf("Enter the number of resources: ");
    scanf("%d", &r);

    available = (int *)malloc(r * sizeof(int));
    total = (int *)malloc(r * sizeof(int));
    max = (int **)malloc(p * sizeof(int *));
    allocation = (int **)malloc(p * sizeof(int *));
    required = (int **)malloc(p * sizeof(int *));

    for(int i = 0; i < p; i++){
        max[i] = (int *)malloc(r * sizeof(int));
        allocation[i] = (int *)malloc(r * sizeof(int));
        required[i] = (int *)malloc(r * sizeof(int));
    }

    getInput(p, r, total, available, max, allocation, required);

    printf("1. Output a safe sequence\n");
    printf("2. Check if a sequence is safe\n");
    printf("3. Given a recourse request sequence, check if the request can be granted\n");
    printf("4. Exit\n");

    while(scanf(" %c", &option) && option != '4'){

        switch(option){
            case '1':
                if(!deadlock && checked){
                    printSeq(safeSeq, p);
                }
                else{
                    if(deadlock){
                        printf("\nNo safe sequence.\n");
                        break;
                    }
                    bool *set = (bool *)calloc(p , sizeof(bool));
                    int* temp = (int *)malloc(r * sizeof(int));
                    memcpy(temp, available, r * sizeof(int));
                    if(!findSafeSeq(temp, allocation, required, p, r, set, safeSeq, 0)){
                        deadlock = true;
                        printf("\nNo safe sequence found.\n");
                    }
                    else{
                        printSeq(safeSeq, p);
                    }
                    checked = true;
                }
                break;

            case '2':
                if(checkProcessSeq(available, allocation, required, p, r)){
                    printf("\nSafe sequence\n");
                }
                break;

            case '3':
                if(checkReqSeq(available, r)){
                    printf("\nRequest can be granted\n");
                } else {
                    printf("\nRequest cannot be granted\n");
                }

                break;

            case '4':
                break;

            default:
                printf("\nInvalid option\n");
                break;

        }
        printf("\nEnter your choice: ");
    }


}


/*
Test case 1:

5
3

10 5 7

7 5 3 
3 2 2
9 0 2
4 2 2
5 3 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Test case 2

4
3

7 3 5

4 3 1
2 1 4 
1 2 1
4 5 4

1 0 1
1 1 3
1 0 1
2 0 0

*/