#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
	int data;
	struct stack *nxt;
} stack;

int check_empty(stack* top)
{
	if(top==NULL)
		return -1;
	else
		return 1;
}

stack* create_stack(int data)
{
	stack *new_stack = (stack*)malloc(sizeof(stack));
	new_stack->data = data;
	new_stack->nxt = NULL;
	return new_stack;
}	

void push(stack** top, stack* new_stack)
{
	stack* temp;
	temp = *top;
	*top = new_stack;
	(*top)->nxt=temp;
}

void pop(stack** top)
{
	if(*top!=NULL)
	{
		stack* temp=*top;
		printf("%d\n",temp->data);
		*top= temp->nxt;
		free(temp);
	}
	else
		printf("-1\n");
		
}


void print_list(stack* top)
{
	stack* temp=top;
	while(temp!=NULL)
	{
		printf("%d ", temp->data);
		temp = temp->nxt;
	}
	printf("\n");
}

void free_list(stack* top)
{
	stack* temp;
	while(top!=NULL)
	{
		temp=top;
		top = top->nxt;		
		free(temp);
	}
}

void main()
{
	char opt;
	int element;
	stack *new_stack,*top=NULL;
	scanf("%c",&opt);
	
	while(opt!='t')
	{
		switch(opt)
		{
			case 'i': scanf("%d",&element);
			new_stack = create_stack(element);
			push(&top,new_stack);
			break;
			case 'd': pop(&top);
			break;
			case 'e': printf("%d\n",check_empty(top));
		}
		scanf("%c",&opt);
	}
	free_list(top);
	
}
				
			
