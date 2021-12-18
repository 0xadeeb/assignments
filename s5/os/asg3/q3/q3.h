#ifndef Q3_H
#define Q3_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void getInput(int p, int r, int* total, int* available, int** max, int ** allocation, int** required);
bool findSafeSeq(int *available, int **allocated, int **required, int p, int r, bool* set, int* seq, int i);
bool checkProcessSeq(int* available, int** required, int** allocation, int p, int r);
bool checkReqSeq(int* available, int r);

#endif