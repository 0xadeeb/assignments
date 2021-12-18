#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
	int key;
	struct tree *right;
	struct tree* left;
	struct tree *parent;	
} tree;

typedef struct stack
{
	tree *t;
	struct stack* next;
}stack;

tree* create_tree(int key)
{
	tree* node = (tree*)malloc(sizeof(tree));
	node->key = key;
	node->right = NULL;
	node->left = NULL;
	node->parent = NULL;
	return node;
}

stack* create_stack(tree* t)
{
	stack* node = (stack*)malloc(sizeof(stack));
	node->t = t;
	node->next = NULL;
	return node;
}

void insert_st(stack** tail, stack* t)
{
	stack *temp = *tail;
	temp->next = t;
	*tail = t;
}

void insert_tree(stack** head, stack* tail)
{
	 stack* cur = * head;
	 tree* parent = cur->t, *child = tail->t;
	 if(parent->left == NULL)
	 {
	 	parent->left = child;
	 	child->parent = parent;
	 }
	 else
	 {
	 	parent->right = child;
	 	child->parent = parent;
	 	*head = cur->next;
	 	free(cur);
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
	stack* head = NULL, *tail = NULL, *new_st;
	tree *root = NULL, *new_tree;
	int key;
	char opt;
	scanf("%c",&opt);
	while( opt != 'e')
	{
		switch(opt)
		{
			case 'i': 
				scanf("%d",&key);
				if(root == NULL)
				{
					root = create_tree(key);
					head = create_stack(root);
					tail = head;
				}
				else
				{
					new_tree = create_tree(key);
					new_st = create_stack(new_tree);
					insert_st(&tail,new_st);
					insert_tree(&head,tail);
				}
				break;
			case 'p':	
				print(root);
				printf("\n");
				break;
		}
		scanf("%c",&opt);
	}

	
}
		

	
