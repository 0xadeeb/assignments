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

typedef struct queue
{
	tree* node;
	struct queue* next;
} queue;
	

tree* create_tree(int key)
{
	tree* node = (tree*)malloc(sizeof(tree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

queue* create_q(tree* root)
{
	queue* n = (queue*)malloc(sizeof(queue));
	n->node = root;
	n->next = NULL;
	return n;
}

tree* build_tree(int *arr, int l, int h)
{
	if(l<h)
	{
		int mid;
		if((l+h)%2 == 0)
			mid = (l+h)/2;
		else
			mid = (l+h)/2 + 1;
		
		tree* root = create_tree(arr[mid]);
		
		root->left = build_tree(arr,l,mid-1);
		root->right = build_tree(arr,mid+1,h);
		return root;
	}
	
	if(l == h)
		return create_tree(arr[l]);
	
	return NULL;
}
void sum(queue* head)
{
	int sum = 0;
	
	while(head!=NULL)
	{
		sum += (head->node)->key;
		head = head->next;
	}
	
	printf("%d ",sum);
	
}

bool levelUp(queue** head)	
{
	queue* h = NULL, *t1 = *head, *t2, *node;
	bool ret = false;
	
	while(t1!=NULL)
	{
		if(h == NULL)
		{
			if(t1!=NULL&& ( t1->node)->left != NULL)
			{
				h = create_q((t1->node)->left);
				if(t1!=NULL&& (t1->node)->right != NULL)
					h->next = create_q((t1->node)->right);
				t2 = h->next;
				ret = true;
			}
			
			else if(t1!=NULL&&(t1->node)->right != NULL)
			{
				h = create_q((t1->node)->right);
				t2 = h;
				ret = true;
			}
			node = t1;
			t1 = t1->next;
			free(node);
		}
		else
		{
			if(t2!=NULL&&t1!=NULL&&(t1->node)->left != NULL)
			{
				t2->next = create_q((t1->node)->left);
				t2 = t2->next;
			}
			
			if(t2!=NULL&&t1!=NULL&&(t1->node)->right != NULL)
			{
				t2->next = create_q((t1->node)->right);
				t2 = t2->next;
			}
			
			node = t1;
			t1 = t1->next;
			free(node);
			
		}
	}
	
	*head = h;
	
	return ret;
}
			
	
void print_sum(tree* root)
{
	queue *head = create_q(root);
	bool cnt = true;
	while(cnt)
	{	
		sum(head);
		cnt = levelUp(&head);
	}

	
}
	
void print(tree* root)
{
	printf("( ");
	if(root!=NULL)
	{
		printf("%d ",root->key);
		print(root->left);
		print(root->right);
	}
	printf(") ");
}

void main()
{
	int n, *arr;
	scanf("%d",&n);
	
	arr = (int*)malloc(n*sizeof(int));
	
	for(int i =0; i<n; i++)
		scanf("%d", arr+i);
	
	
	tree* root = build_tree(arr,0,n-1);
	
	print_sum(root);
	printf("\n");
	
}
