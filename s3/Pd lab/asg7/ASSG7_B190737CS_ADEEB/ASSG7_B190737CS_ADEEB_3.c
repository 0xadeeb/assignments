#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
	int *q , front, rear, n;
} queue;

int check_full(queue *que)
{
	if(que->rear == que->front)
		return -1;
	else 
		return 1;
}

int check_empty(queue* que)
{
	if(que->front == -1)
		return -1;
	else
	 	return 1;
}

void iqueue(queue* que, int element)
{
	if(check_full(que)==-1)
		printf("-1\n");
	
	else if(check_empty(que)==-1)
	{
		
		que->front=0;
		*(que->q) = element;
		que->rear = 1;
	}
	
	else 
	{
		*(que->q + que->rear) = element;
		que->rear = (que->rear+1)%que->n;
	}
}

void dqueue( queue* que )
{
	if(check_empty(que)==-1)
		printf("-1\n");
		
	else if(que->rear == (que->front+1)%que->n )
	{
		printf("%d\n",*(que->q + que->front));
		que->front=-1;
		que->rear = 0;
	}
	
	else
	{
		printf("%d\n",*(que->q + que->front));
		que->front = (que->front+1)%que->n;
	}
}	


void main()
{
	queue *que = (queue*)malloc(sizeof(queue));
	scanf("%d",&que->n);
	que->q = (int*)malloc(que->n* sizeof(int));
	que->front=-1;
	que->rear = 0;
	
	char opt;
	int element;
	scanf("%c",&opt);
	
	while(opt!='t')
	{
		switch(opt)
		{
			case 'i': scanf("%d",&element);
			iqueue(que,element);
			break;
			case 'd': dqueue(que);
			break;
			case 'f': printf("%d\n",check_full(que));
			break;
			case 'e': printf("%d\n",check_empty(que));
		}
		scanf("%c",&opt);
	}
	free(que->q); 
	free(que);
}
