#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int id;
	char state[15];
	struct node *nxt;
} node;

node* list_search(node* head, int element)
{
	node* temp=head;
	
	while(temp!=NULL&&temp->id!=element)
		temp= temp->nxt;
		
	return temp;
	
}
		

node* create_node(int id, char* state)
{
	node *new_node = (node*)malloc(sizeof(node));
	new_node->id = id;
	strcpy(new_node->state,state);
	new_node->nxt = NULL;
	return new_node;
}	

void list_insert_front(node** head, node* new_node)
{
	node* temp;
	temp = *head;
	*head = new_node;
	(*head)->nxt=temp;

}

void list_insert_tail(node** head, node* new_node)
{
	node* temp=*head;
	
	if(*head==NULL)
		*head= new_node;
	else
	while(temp->nxt!=NULL)
		temp=temp->nxt;
	temp->nxt = new_node;

}	

void list_insert_before(node** head, node* new_node, node* insert_pos)
{
	node *temp = *head;
	
	if(*head==insert_pos)
		list_insert_front(head,new_node);
		
	else
	{
		while(temp->nxt!=insert_pos)
			temp= temp->nxt;
		
		new_node->nxt=temp->nxt;
		temp->nxt = new_node;
	}

}

void list_insert_after(node** head, node* new_node, node* insert_pos)
{
	node *temp = *head;
	
	while(temp!=insert_pos)
		temp= temp->nxt;
	
	new_node->nxt=temp->nxt;
	temp->nxt = new_node;
	
}

void list_delete_first(node** head)
{
	if(head!=NULL)
	{
		node* temp = *head;
		printf("%d\n",(*head)->id);
		*head= (*head)->nxt;
		free(temp);
	}
	else
		printf("-1\n");
		
}

	
void list_delete(node** head, node* del_pos)
{
		
	if(*head!=NULL&&del_pos!=NULL)
	{
		if(*head==del_pos)
			list_delete_first(head);
		else
		{
			node *temp=*head, *p;
			
			while(temp->nxt!=del_pos)
				temp= temp->nxt;
			
			p=temp->nxt;
			temp->nxt = p->nxt;
			printf("%d\n",p->id);
			free(p);
		}
	}
	else
		printf("-1\n");
		
	
}

void list_delete_last(node** head)
{
	if(head!=NULL)
	{
		node *temp=*head, *p=(*head)->nxt;
		
		while(p->nxt!=NULL)
		{
			temp= temp->nxt;
			p = p->nxt;
		}
		
		temp->nxt = NULL;
		printf("%d\n",p->id);
		free(p);
	}
	else
		printf("-1\n");
	
	
}

void waiting_ids(node** head)
{
	node* temp = *head;
	while(temp!=NULL)
	{
		if(strcmp("waiting",temp->state)==0)
			printf("%d ", temp->id);
		temp = temp->nxt;
	}
	printf("\n");
}

void print_list(node** head)
{
	node* temp = *head;
	while(temp!=NULL)
	{
		printf("(%d,%s) ", temp->id, temp->state);
		temp = temp->nxt;
	}
	printf("\n");
}

void free_list(node** head)
{
	node* temp;
	while(*head!=NULL)
	{
		temp=*head;
		*head = (*head)->nxt;		
		free(temp);
	}
}

void main()
{
	char opt,state[20];
	int x,y;
	node *new_node,*insert_pos,*del_pos,*head=NULL;
	scanf("%c",&opt);

	
	while(opt!='e')
	{
		switch(opt)
		{
			case 'i': scanf("%d%s",&x,state);
			new_node=create_node(x,state);
			if(head==NULL)
				head=new_node;
			else
			{
				list_insert_front(&head,new_node);
				//print_list(&head);
			}
			break;
			case 'd': scanf("%d",&x);
			del_pos= list_search(head,x);
			list_delete(&head,del_pos);
			//print_list(&head);
			break;
			case 'g': scanf("%d",&x);
			new_node=list_search(head,x);
			if(new_node==NULL)
				printf("-1\n");
			else 	
				printf("%s\n",new_node->state);
			break;
			
			case 'l':waiting_ids(&head);
			break;
			
			case 'u': scanf("%d%s",&x,state);
			new_node = list_search(head,x);
			if(new_node!=NULL)
				strcpy(new_node->state,state);
			//print_list(&head);
				
		}
		scanf("%c",&opt);
	}
	free_list(&head);
	
}
				
			
