#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int id;
	char p[15], state[15];
	struct node *nxt;
} node;


node* create_node(char* p, int* selected_ids, int c)
{
	node *new_node = (node*)malloc(sizeof(node));
	strcpy(new_node->p , p);
	strcpy(new_node->state , "new");
	new_node->nxt = NULL;
	
	for(int i=0;i<c;i++)
		if(selected_ids[i]==0)
		{
			new_node->id = i+1;
			selected_ids[i]=1;
			break;
		}
	
	
	return new_node;
}

node* list_search(node* head, int j)
{
	node* temp=head;
	
	while(temp!=NULL&&temp->id!=j)
		temp= temp->nxt;
		
	return temp;
	
}

void insert_node (node** head, node* new_node)
{
	node* temp= *head;
	
	if(*head==NULL)
		*head= new_node;
	else
	{	
		while(temp->nxt!=NULL)
			temp=temp->nxt;
	
	temp->nxt = new_node;
	}
}

void list_process(node* head)
{
	node* temp=head;
	if(head==NULL)
		printf("-1\n");
	while(temp!=NULL)
	{
		printf("%d ", temp->id);
		temp = temp->nxt;
	}
	printf("\n");
}

void update_state(node* pos , node** s1, node** s2)
{
	node *temp = *s1, *tmp1 = *s2, *tmp2;
	
	if(pos == *s1)
		*s1 = pos->nxt;
	else
	{
		while(temp->nxt!=pos)
			temp= temp->nxt;
		node* x =temp;
		temp = temp->nxt;
		x->nxt = temp->nxt;
	}
	
	if(tmp1==NULL)
	{
		pos->nxt = NULL;	
		*s2=pos;
	}
	
	else
	{
		tmp2 = tmp1->nxt;

		if(strcmp(pos->p,"high")==0)
		{
			while(tmp2!=NULL&&strcmp(tmp2->p,"medium")!=0)
			{
				tmp1= tmp1->nxt;
				tmp2= tmp2->nxt;
			}
			
			tmp1->nxt = pos;
			pos->nxt = tmp2;
		}
		
		if(strcmp(pos->p,"medium")==0)
		{
			while(tmp2!=NULL&&strcmp(tmp2->p,"low")!=0)
			{
				tmp1= tmp1->nxt;
				tmp2= tmp2->nxt;
			}
			
			tmp1->nxt = pos;
			pos->nxt = tmp2;
		}
		if(strcmp(pos->p,"low")==0)
		{
			while(tmp1->nxt!=NULL)
				tmp1 = tmp1->nxt ; 
				
			tmp1->nxt = pos;
			pos->nxt = NULL;
		}
	}
}
			
void schedule(node ** ready, node** running)
{
	node* temp = *ready;
	*running = *ready;
	*ready = temp->nxt;
}

void terminate( node** t, node** running, int* selected_ids)
{
	node* temp = *t,* tmp= *running;
	*(selected_ids + tmp->id -1)=0;
	tmp->id = 999;
	if(*t== NULL)
		*t = *running;
	else
	{
		while(temp->nxt == NULL)
			temp= temp->nxt;
		
		temp->nxt = *running;
	}
	*running == NULL;
}

void main()
{
	int j;
	char opt, p[15],s1[15],s2[15];
	int *selected_ids= (int*)calloc(1,sizeof(int)), c=0;
	node *r = NULL, *t= NULL, *n= NULL, *w= NULL, *running=NULL, *new_node, *pos;
	scanf("%c",&opt);
	while( opt != 'e')
	{
		switch(opt)
		{
			case 'c': 
				selected_ids = (int*)realloc(selected_ids, ++c* sizeof(int));
				scanf("%s",p);
				new_node = create_node(p,selected_ids,c);
				insert_node(&n, new_node);
				break;
			case 'l': scanf("%d",&j);
				switch(j)
				{
					case 1: list_process(n);
					break;
					case 2: list_process(r);
					break;
					case 3: list_process(w);
					break;
					case 4: list_process(t);
				}
				break;
			case 'u': 
				scanf("%d%s%s", &j, s1, s2);
				
				if(strcmp(s1,"running")==0 && running!=NULL)
				{
					strcpy(running->state, "waiting");
					update_state(running, &running, &w);

				}
				
				if(strcmp(s1,"new")==0)
				{
					pos = list_search(n,j);
					*(selected_ids + pos->id -1)=0;
					strcpy(pos->state,"ready");
					update_state(pos, &n, &r);
				
				}
				else
				{
					pos = list_search(w,j);
					strcpy(pos->state,"ready");
					update_state(pos, &w, &r);
				}
				break;
			case 's':
				if(running==NULL)
					printf("-1\n");
				else
					schedule(&r , &running);
				break;
			case 't': 
				c--;
				terminate(&t , &running, selected_ids);

		}
		if(running==NULL&&r!=NULL)
			schedule(&r,&running);
		scanf("%c",&opt);
	}
		
		
}
					
			
			
			
			
			
			
			
			
			
			
			
