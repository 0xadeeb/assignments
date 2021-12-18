#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	float grade;
	char name[20];
	struct student *nxt;
} student;

student* create_node()
{
	student* node;
	node = (student*)malloc(sizeof(student));
	scanf("%s%f", node->name, &node->grade);
	node->nxt = NULL;
	return node;
}

void insert_node(student *head, student *node)
{
	student* temp = head;
	while ( temp->nxt != NULL)
		temp = temp->nxt;
	temp->nxt = node;
}

student* find_pos(student* head, float grade)
{
	student* temp=head;
	while( temp!=NULL)
	{	
		if( temp->grade > grade)
			break;
		temp = temp->nxt;
	}
	return temp;
}

void insert_before(student **head, student *pos, student *node)
{
	student *temp = *head;
	
	if( pos == *head)
	{
		*head = node;
		node->nxt = temp;
	}
	
	else
	{
		while(temp->nxt != pos)
			temp = temp->nxt;
		
		node->nxt = temp->nxt;
		temp->nxt = node;
	}
	
}
void print_list(student* head)
{
	printf("\n");
	student *temp=head;
	while(temp!=NULL)
	{
		printf("%s %.2f\n", temp->name, temp->grade);
		temp = temp->nxt;
	}
	
}

void main()
{
	int n1, n2;
	scanf("%d%d",&n1,&n2);
	student *head1, *head2,*temp,*node,*pos;
	
	head1 = create_node();
	for(int i= 1; i< n1; i++)
	{
		node = create_node();
		insert_node(head1,node);
	}
	
	head2 = create_node();
	for(int j= 1; j< n2; j++)
	{
		
		node = create_node();
		insert_node(head2,node);
	}
	
	temp = head1;
	
	while(temp!=NULL)
	{	
		pos = find_pos(head2, temp->grade);
		node = (student*)malloc(sizeof(student));
		node->grade = temp->grade;
		strcpy(node->name,temp->name);
		insert_before(&head2, pos, node);
		temp = temp->nxt;
	}
	
	print_list(head2);
}

/*
4 3
ab1 5.01
ab2 6.92
ab3 7.01
ab4 8.08
xy1 6.51
xy2 8.92
xy2 9.07*/

















