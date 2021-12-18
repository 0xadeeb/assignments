#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int id;
	char p[15], state[15];
	struct node *nxt;
} node;

int issafe(int id, int*selected_ids)
{
	if(selected_ids[id]==0)
		return 1;
	return 0;
}


node* create_node(char* p, int* selected_ids, int c)
{
	node *new_node = (node*)malloc(sizeof(node));
	strcpy(new_node->p , p);
	strcpy(new_node->state , "new");
	new_node->nxt = NULL;
	int i =1;
	
	for(;i<=c;i++)
	{
		if(issafe(i,selected_ids))
		{
			new_node->id = i;
			selected_id[i]=1;
		}
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
	while(temp->nxt!=NULL)
		temp=temp->nxt;
	temp->nxt = new_node;
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

void update_state( node* pos , node** s1, node** s2)
{
	node * temp = *s1, *tmp1 = *s2, *tmp2;
	tmp2 = tmp1->nxt;
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
	if(strcmp(pos->p,"high")==0)
	{
		
		while(strcmp(tmp2->p,"medium")==0)
		{
			tmp1= tmp1->nxt;
			tmp2= tmp2->nxt;
		}
		tmp1->nxt = pos;
		pos->nxt = tmp2;
	}
	if(strcmp(pos->p,"medium")==0)
	{
		
		while(strcmp(tmp2->p,"low")==0)
		{
			tmp1= tmp1->nxt;
			tmp2= tmp2->nxt;
		}
		tmp1->nxt = pos;
		pos->nxt = tmp2;
	}
	else
	{
		while(tmp1->nxt!=NULL)
			tmp1->nxt = pos;
			pos->nxt = NULL;
	}
}
			
void schedule(node ** ready, node** running)
{
	node* temp = *ready ;
	*running = *ready;
	*ready = temp->nxt;
}

void terminate( node** t, node** running, int* selected_ids)
{
	node* temp = *t;
	*(selected_ids + *(running)->id)=0;
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
	node *r = NULL, *t= NULL, *n= NULL, *w= NULL, *running=NULL;
	
	
	char opt, p[15],s1[15],s2[15], running[15];
	int *seleced_ids= (int*)calloc(1,sizeof(int)), c=0;
	node* new_node, *pos;
	scanf("%c",opt);
	
	while( opt != 'e')
	{
		switch(opt)
		{
			case 'c': scanf("%s",p);
			selected_ids = (int*)realloc(seleted_ids, ++c* sizeof(int))
			new_node = create_node(p,selected_ids,c);
			insert_node(&n, new_node);
			break;
			case 'i': scanf("%d",j);
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
			case 'u': scanf("%d%s%s", j, s1, s2);
			
			if(strcmp(s1,"running")==0 && running!=NULL)
			{
				update_state(running, &running, &w);
				schedule(&r,&running);
			}
			
			if(strcmp(s1,"new")==0)
			{
				pos = list_search(n,j);
				update_state(pos, &n, &r);
			
			}
			else
			{
				pos = list_search(w,j);
				update_state(pos, &w, &rh);
			}
			break;
			case 's':
				schedule(&r , &running);
				break;
			case 't': 
				terminate(&t , &running, selected_ids);
				
			scanf("%c",opt);
			}
		}
		
		
}
					
			
			
			
			
			
			
			
			
			
			
			
