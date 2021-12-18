#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack
{
	int n,top;
	char *s;
} stack;


void push(stack* stk, char element)
{
	
	stk->top++;
	*(stk->s + stk->top) = element;
	
}

char pop(stack* stk)
{ 
	char ans = *(stk->s + stk->top);
 	stk->top--;
 	return ans;
	 
}	 	

int check_palindrom(stack* stk, char* str)
{
	char *temp;
	temp = (char*)malloc(stk->n* sizeof(char));
	for(int i=0; i< stk->n; i++)
		push(stk, str[i]);
	for(int i=0; i< stk->n; i++)
		temp[i] = pop(stk);
		
	if(strcmp(temp,str)==0)
		return 1;
	else
		return 0;
}

void main()
{
	stack* stk = (stack*)malloc(sizeof(stack));
	char str[1000];
	scanf("%s",str);
	stk->n = strlen(str);
	stk->s = (char*)malloc(sizeof(char)*stk->n);
	stk->top = -1;
	
	printf("%d\n",check_palindrom(stk,str));
	free(stk->s); 
	free(stk);
}
			
