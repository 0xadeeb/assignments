#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue
{
	int pages;
	float size;
	char id[10], name[10];
	struct queue *nxt;
} queue;


queue* create_queue(char* id, char* name, int pages, float size)
{
	queue *new_queue = (queue*)malloc(sizeof(queue));
	new_queue->pages = pages;
	new_queue->size = size;
	strcpy(new_queue->id, id);
	strcpy(new_queue->name, name);
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
		printf("%s\n",temp->id);
		if(*front == *rear)
			*rear = NULL;
		*front= temp->nxt;
		//printf("%lf\n",*front);
		//printf("%lf\n",NULL);
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

void print_queue(queue* front)
{
	queue* temp=front;
	if(front == NULL)
		printf("-1\n");
	else
	{
		while(temp!=NULL)
		{
			printf("%s %s %d %.1f\n",temp->id, temp->name, temp->pages, temp->size);
			temp = temp->nxt;
		}
		
	}
}

void main()
{
	char id[15],name[15], opt;
	int pages;
	float size;
	
	queue *new_queue,*front=NULL,*rear=NULL;
	scanf("%c",&opt);

	
	while(opt!='t')
	{
		switch(opt)
		{
			case 'a': scanf("%s%s%d%f",id,name,&pages,&size);
			new_queue = create_queue(id,name,pages,size);
			iqueue(&front,&rear,new_queue);
			break;
			case 'e': dqueue(&front,&rear);
			break;
			case 'l': print_queue(front);
		}
		scanf("%c",&opt);
	}
	free_list(front);
	
}
				
			
