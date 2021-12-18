#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct tree
{
	int key;
	struct tree* right;
	struct tree* left;
} tree;

typedef struct ll
{
	int key;
	struct ll* next;
	struct ll* prev;
} ll;

tree* create_tree(int key)
{
	tree* node = (tree*)malloc(sizeof(tree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

ll* create_ll(int key)
{
	ll* node = (ll*)malloc(sizeof(ll));
	node->key = key;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void push(ll** head, ll** tail, int key)
{
	ll* node = create_ll(key);
	
	if(*head == NULL)
	{
		*head = node;
		*tail = node;
	}
	
	else
	{
		(*tail)->next = node;
		node->prev = *tail;
		*tail = node;
	}
}
	
void pop_t(ll** head, ll** tail)
{
	ll* t = *tail;
	if(*head == *tail)
	{
		*head = NULL;
		*tail = NULL;
		free(t);
	}
	
	else
	{
		*tail = t->prev;
		(*tail)->next = NULL;
		free(t);
	}
}	

void pop_h(ll** head, ll** tail)
{
	ll* t = *head;
	if(*head == *tail)
	{
		*head = NULL;
		*tail = NULL;
		free(t);
	}
	
	else
	{
		*head = t->next;
		(*head)->prev = NULL;
		free(t);
	}
}

bool getLink(ll** head, ll** tail, tree* root, int key)
{
	if(root == NULL)
		return false;
		
	push(head,tail,root->key);
	
	if(root->key == key)
		return true;
	
	if(getLink(head, tail, root->left, key) || getLink( head, tail, root->right, key) )
		return true;
	
	pop_t(head,tail);
	
	return false;
}

int max_path(ll** h1, ll** h2, ll** t1, ll** t2)
{
	int max = -1000000;
	
	while((*h1!=NULL&&*h2!=NULL) && ((*h1)->key == (*h2)->key ) )
	{
		max = (*h1)->key;
		pop_h(h1,t1);
		pop_h(h2,t2);
	}	
	
	ll* tail = *t1, *head = *h2, *node;
	
	if(tail!=NULL)
	{
		tail = tail->prev;
		if(tail!=NULL)
			tail->next = NULL;
	}
	
	if(*t2!=NULL)
	{
		*t2 = (*t2)->prev;
		if(*t2!=NULL)
			(*t2)->next = NULL;
	}
	
	
	
	while( tail != NULL)
	{
		
		if(tail->key > max)
			max = tail->key;
		node = tail;
		tail = tail->prev;
		free(node);
	}
	
	while( head != NULL)
	{
		
		if(head->key > max )
			max = head->key;
		node = head;
		head = head->next;
		free(node);
	}
	
	return max;

}

void insert(tree* root, int key)
{
	if(key < root->key)	
	{
		if(root->left == NULL)
			root->left = create_tree(key);
		
		else
			insert(root->left, key);
	}
	
	else
	{
		if(root->right == NULL)
			root->right = create_tree(key);
		
		else
			insert(root->right, key);
	}
}

void print(ll* head)
{
	while(head!=NULL)
	{
		printf("%d ",head->key);
		head = head->next;
	}
}

void print_t(tree* root)
{
	printf("( ");
	if(root!=NULL)
	{
		printf("%d ",root->key);
		print_t(root->left);
		print_t(root->right);
	}
	printf(") ");
}
		

void main()
{
	char c;
	int num=0, n1, n2,key;
	bool neg = false;
	tree* root = NULL;
	ll* n1_head = NULL, *n2_head = NULL, *n1_tail = NULL, *n2_tail = NULL;
	
	while(scanf("%c",&c) && c!='\n')
	{
		if(c == '-')
			neg = true;
		
		if(isdigit(c))
		{
			if(neg)
				num = -1 * (c - 48);
			else
				num = num*10 + (c - 48);
			neg = false;
		}
		
		if(c == ' ')
		{
			if(root == NULL)
				root = create_tree(num);
			else
				insert(root,num);
			num = 0;
		}
	
	}
	
	insert(root,num);
	
	
	scanf("%d %d",&n1,&n2);
	
	getLink(&n1_head, &n1_tail, root, n1);
	getLink(&n2_head, &n2_tail, root, n2);

	printf("%d\n",max_path(&n1_head, &n2_head, &n1_tail, &n2_tail));
	
}
	
	
				
		
	

