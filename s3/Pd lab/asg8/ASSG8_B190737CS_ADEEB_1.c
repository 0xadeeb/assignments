#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>

typedef struct stack
{
	char key;
	struct stack* nxt;
} stack;
	

int priority(char x)
{
	if(x == '*' || x == '/')
		return 2;
	if(x == '(')
		return 0;
	else
		return 1;
}

void push( stack** top, char x)
{
	stack* node= (stack*)malloc(sizeof(stack));
	node->key = x;
	node->nxt = *top;
	*top = node;
}

char pop(stack **top)
{
	char x;
	stack *temp = *top;
	*top = temp->nxt;
	x = temp->key;
	free(temp);
	return x;
}		


void main()
{
	stack* top=NULL;
	char *str = (char*)malloc(INT_MAX* sizeof(char));
	scanf("%s",str);
	str = (char*)realloc(str, strlen(str)*sizeof(char));
	
	for(int i=0; i<strlen(str); i++)
	{
		if(isalpha(str[i]))
			printf("%c",str[i]);
		
		else if(str[i]=='(')
			push(&top,'(');
			
		else if ( str[i] == ')')
		{
			while(top->key != '(')
				printf("%c",pop(&top));
			pop(&top);
		}
		else
		{
			while(top!=NULL&&priority(str[i])<=priority(top->key))
				printf("%c",pop(&top));
			push(&top,str[i]);		
		}	
	}
	
	while( top != NULL)
		printf("%c",pop(&top));
		
}	
