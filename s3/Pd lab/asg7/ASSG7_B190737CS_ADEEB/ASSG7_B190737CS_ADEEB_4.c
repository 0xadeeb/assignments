#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
	int data;
	struct queue *nxt;
} queue;


queue* create_queue(int data)
{
	queue *new_queue = (queue*)malloc(sizeof(queue));
	new_queue->data = data;
	new_queue->nxt = NULL;
	return new_queue;
}	

int check_empty(queue* front)
{
	if(front == NULL)
		return -1;
	else 
		return 1;
}

void iqueue(queue** front,queue** rear, queue* new_queue)
{
	queue* temp=*rear;
	
	if(*front==NULL)
	{	
		*front= new_queue;
		*rear = new_queue;
	}
	
	else
	{
		temp->nxt = new_queue;
		*rear = new_queue;
	}
}	


void dqueue(queue** front, queue** rear)
{
	if(*front==NULL)
		printf("-1\n");
	else
	{
		queue* temp=*front;
		printf("%d\n",temp->data);
		if(*front == *rear)
			*rear = NULL;
		*front= temp->nxt;
		free(temp);
	}
	
		
		
}

void free_list(queue* front)
{
	queue* temp;
	while(front!=NULL)
	{
		temp=front;
		front = front->nxt;		
		free(temp);
	}
}

void main()
{
	char opt;
	int element;
	queue *new_queue,*front=NULL,*rear=NULL;
	scanf("%c",&opt);

	
	while(opt!='t')
	{
		switch(opt)
		{
			case 'i': scanf("%d",&element);
			new_queue = create_queue(element);
			iqueue(&front,&rear,new_queue);
			break;
			case 'd': dqueue(&front,&rear);
			break;
			case 'e': printf("%d\n",check_empty(front));
		}
		scanf("%c",&opt);
	}
	free_list(front);
	
}
				
			
