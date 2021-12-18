#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
	int *s,n,top;
} stack;


int check_empty(stack* stk)
{
	if(stk->top==-1)
		return -1;
	else
		return 1;
}

void push(stack* stk, int element)
{
	if(stk->top==stk->n-1)
		printf("-1\n");
		
	else
	{
		stk->top++;
		*(stk->s + stk->top) = element;
	}
}

void pop(stack* stk)
{
	 if(check_empty(stk)==-1)
	 	printf("-1\n");
	 else
	 {
	 	printf("%d\n",*(stk->s + stk->top));
	 	stk->top--;
	 }
}	 	


void main()
{
	stack* stk = (stack*)malloc(sizeof(stack));
	scanf("%d",&stk->n);
	stk->s = (int*)malloc(sizeof(int)*stk->n);
	stk->top = -1;
	char opt;
	int element;
	scanf("%c",&opt);
	
	while(opt!='t')
	{
		switch(opt)
		{
			case 'i': scanf("%d",&element);
			push(stk,element);
			break;
			case 'd': pop(stk);
			break;
			case 'e': printf("%d\n",check_empty(stk));
		}
		scanf("%c",&opt);
	}
	free(stk->s); 
	free(stk);
}
			
