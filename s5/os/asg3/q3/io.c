#include "q3.h"

void getInput(int p, int r, int* total, int* available, int** max, int ** allocation, int** required){

    printf("Enter the total resources available :\n");
    for(int i = 0; i < r; i++){
        scanf("%d", &total[i]);
    }
    printf("\n");

    printf("Enter the maximum resources:\n");
    for(int i = 0; i < p; i++){
        for(int j = 0; j < r; j++){
            scanf("%d", &max[i][j]);
        }
    }
    printf("\n");

    printf("Enter the allocation matrix:\n");

    for(int i = 0; i < p; i++){
        for(int j = 0; j < r; j++){
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\n");

    printf("Resources avalable for each process: ");
    for(int j = 0; j < r; j++){
        available[j] = total[j];
        for(int i = 0; i < p; i++){
            available[j] -= allocation[i][j];
        }
        printf("%d ", available[j]);
    }
    printf("\n\n");

    printf("Required matrix:\n");
    for(int i = 0; i < p; i++){
        for(int j = 0; j < r; j++){
            required[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", required[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}