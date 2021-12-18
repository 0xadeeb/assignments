#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
typedef struct stack{
    int seat, newP, oldP;
    char operation[20];
    struct stack *next;
} stack;

stack* createNode(int seat, char operation[20], int newP, int oldP){
    stack *new_stack = (stack*)malloc(sizeof(stack));
    new_stack->seat = seat;
    new_stack->newP = newP;
    new_stack->oldP = oldP;
    strcpy(new_stack->operation, operation);
    new_stack->next = NULL;
    return new_stack;
}

void push(stack **top, stack* new){
    new->next = *top;
    *top = new;
}

void book_seat(int* A, stack** S){
    int seat, pid;
    scanf("%d", &pid);
    scanf("%d", &seat);
    int oldP = A[seat - 1];
    A[seat - 1] = pid;
    push(S, createNode(seat, "book", pid, oldP));
}

void cancel_seat(int* A, stack** S){
    int seat;
    scanf("%d", &seat);
    int oldP = A[seat - 1];
    A[seat - 1] = 0;
    push(S, createNode(seat, "cancel", 0, oldP));
}

void undo(int* A, stack** top){
    if(*top == NULL){
        return;
    }
    stack* temp = *top;
    int seat = temp->seat;
    A[seat - 1] = temp->oldP;
    *top = temp->next;
    free(temp);
}

void display(int* A){
    for(int i = n - 1; i >= 0; i--){
        printf("%d ", A[i]);
    }
    printf("\n");
}

void main(){
    scanf("%d", &n);
    int* A = (int*)calloc(n, sizeof(int));
    stack* S = NULL;

    char opt;

    while(scanf("%c", &opt) && opt != 't'){
        switch(opt){
            case 'i':
                book_seat(A, &S);
                break;
            case 'd':
                cancel_seat(A, &S);
                break;
            case 'u':
                undo(A, &S);
                break;
            case 'p':
                display(A);
                break;
        }
    }

}