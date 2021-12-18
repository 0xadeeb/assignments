#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>

typedef struct stack
{
	double key;
	struct stack* nxt;
} stack;


void push( stack** top, double x)
{
	stack* node= (stack*)malloc(sizeof(stack));
	node->key = x;
	node->nxt = *top;
	*top = node;
}

double pop(stack **top)
{
	double x;
	stack *temp = *top;
	*top = temp->nxt;
	x = temp->key;
	free(temp);
	return x;
}		
	
double evaluate_postfix(char *str)
{
	double x,y;
	stack* top=NULL;
	for( int i=0; i< strlen(str); i++)
	{	
		if(isdigit(str[i]))
		{
			double z=atoi(&str[i++]);;
			while(str[i]!=' ')
				i++;
			
			push(&top,z);
		}
		else if( str[i] == '+')
		{
			x = pop(&top);
			y = pop(&top);
			push(&top, (x+y));
		}
		else if( str[i] == '-')
		{
			x = pop(&top);
			y = pop(&top);
			push(&top,(y-x));
		}
		else if( str[i] == '*')
		{
			x = pop(&top);
			y = pop(&top);
			push(&top, (x*y));
		}
		else if( str[i] == '/')
		{
			x = pop(&top);
			y = pop(&top);
			push(&top,(y/x));
		}
	}
	return pop(&top);
}
		
void main()
{
	char *str = (char*)malloc(INT_MAX* sizeof(char));
	scanf("%[^\n]%*c",str);
	str = (char*)realloc(str, strlen(str)*sizeof(char));
	printf("%.0lf",evaluate_postfix(str));
	
}
