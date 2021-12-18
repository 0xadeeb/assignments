#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *nxt;
} node;

node* list_search(node* head, int element)
{
	node* temp=head;
	
	while(temp!=NULL&&temp->data!=element)
		temp= temp->nxt;
		
	return temp;
	
}
		

node* create_node(int data)
{
	node *new_node = (node*)malloc(sizeof(node));
	new_node->data = data;
	new_node->nxt = NULL;
	return new_node;
}	

node* list_insert_front(node* head, node* new_node)
{
	node* temp;
	temp = head;
	head = new_node;
	head->nxt=temp;
	return head;
}

node* list_insert_tail(node* head, node* new_node)
{
	node* temp=head;
	
	if(head==NULL)
		head= new_node;
	else
	while(temp->nxt!=NULL)
		temp=temp->nxt;
	temp->nxt = new_node;
	return head;
}	

node* list_insert_before(node* head, node* new_node, node* insert_pos)
{
	node *temp=head;
	
	if(head==insert_pos)
		head= list_insert_front(head,new_node);
		
	else
	{
		while(temp->nxt!=insert_pos)
			temp= temp->nxt;
		
		new_node->nxt=temp->nxt;
		temp->nxt = new_node;
	}
	return head;
}

node* list_insert_after(node* head, node* new_node, node* insert_pos)
{
	node *temp=head;
	
	while(temp!=insert_pos)
		temp= temp->nxt;
	
	new_node->nxt=temp->nxt;
	temp->nxt = new_node;
	return head;
}

node* list_delete_first(node* head)
{
	if(head!=NULL)
	{
		node* temp=head;
		printf("%d\n",head->data);
		head= head->nxt;
		free(temp);
	}
	else
		printf("-1\n");
		
	return head;
}

	
node* list_delete(node* head, node* del_pos)
{
		
	if(head!=NULL&&del_pos!=NULL)
	{
		if(head==del_pos)
			head = list_delete_first(head);
		else
		{
			node *temp=head, *p;
			
			while(temp->nxt!=del_pos)
				temp= temp->nxt;
			
			p=temp->nxt;
			temp->nxt = p->nxt;
			printf("%d\n",p->data);
			free(p);
		}
	}
	else
		printf("-1\n");
		
	return head;
}

node* list_delete_last(node* head)
{
	if(head!=NULL)
	{
		node *temp=head, *p=head->nxt;
		
		while(p->nxt!=NULL)
		{
			temp= temp->nxt;
			p = p->nxt;
		}
		
		temp->nxt = NULL;
		printf("%d\n",p->data);
		free(p);
	}
	else
		printf("-1\n");
	
	return head;
}

void print_list(node* head)
{
	node* temp=head;
	while(temp!=NULL)
	{
		printf("%d ", temp->data);
		temp = temp->nxt;
	}
	printf("\n");
}

void free_list(node* head)
{
	node* temp;
	while(head!=NULL)
	{
		temp=head;
		head = head->nxt;		
		free(temp);
	}
}

void main()
{
	char opt;
	int x,y;
	node *new_node,*insert_pos,*del_pos,*head=NULL;
	scanf("%c",&opt);

	
	while(opt!='e')
	{
		switch(opt)
		{
			case 'f': scanf("%d",&x);
			new_node=create_node(x);
			if(head==NULL)
				head=new_node;
			else
			head =list_insert_front(head,new_node);
			//print_list(head);}
			break;
			case 't': scanf("%d",&x);
			new_node=create_node(x);
			if(head==NULL)
				head=new_node;
			else
				head=list_insert_tail(head,new_node);
			//print_list(head);
			break;
			case 'a': scanf("%d %d",&x,&y);
			new_node= create_node(x);
			insert_pos= list_search(head,y);
			head=list_insert_after(head,new_node,insert_pos);
			//print_list(head);
			break;
			case 'b': scanf("%d %d",&x,&y);
			new_node= create_node(x);
			insert_pos= list_search(head,y);
			head=list_insert_before(head,new_node,insert_pos);
			//print_list(head);
			break;
			case 'd': scanf("%d",&x);
			del_pos= list_search(head,x);
			head=list_delete(head,del_pos);
			//print_list(head);
			break;
			case 'i': head=list_delete_first(head);
			//print_list(head);
			break;
			case 'l': head=list_delete_last(head);
			//print_list(head);
			break;
			case 's': scanf("%d",&x);
			new_node=list_search(head,x);
			if(new_node==NULL)
				printf("-1\n");
			else 	
				printf("1\n");
				
		}
		scanf("%c",&opt);
	}
	free_list(head);
	
}
				
			
