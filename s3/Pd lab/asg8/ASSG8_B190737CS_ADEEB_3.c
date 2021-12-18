#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct tree
{
	char key;
	struct tree *r, *l;
} tree;

typedef struct stack
{
	struct tree *parent;
	struct stack *nxt;
} stack;

void push(stack** top, tree* subtree)
{
	stack* node= (stack*)malloc(sizeof(stack));
	node->parent = subtree;
	node->nxt = *top;
	*top = node;
}

tree* pop(stack **top)
{
	tree* root;
	stack *temp = *(top);
	*top = temp->nxt;
	root = temp->parent;
	free(temp);
	return root;
}

tree* create_tree(char s,tree* l, tree* r)
{
	tree *subtree = (tree*)malloc(sizeof(tree));
	subtree->key = s;
	subtree->r = r;
	subtree->l = l;
	return subtree;
}

tree* construct_tree(char *str)
{
	stack* top = NULL;
	tree *subtree = NULL, *r = (tree*)malloc(sizeof(tree)), *l= (tree*)malloc(sizeof(tree));
	for( int i=0; i< strlen(str); i++)
	{	
		if(isalpha(str[i]))
		{
			
			subtree = create_tree(str[i],NULL,NULL);
			push(&top , subtree);
			
		}
		else 
		{
			r = pop(&top);
			l = pop(&top);
			subtree = create_tree(str[i],l,r);
			push(&top, subtree);
		}
	}
	return pop(&top);
	
}

void inorder(tree* root)
{
	if(root!=NULL)
	{
		inorder(root->l);
		printf("%c",root->key);
		inorder(root->r);
	}
	
}

void preorder(tree* root)
{
	if(root!=NULL)
	{
		printf("%c",root->key);
		preorder(root->l);
		preorder(root->r);
	}
}

void postorder(tree* root)
{
	if(root!=NULL)
	{
		postorder(root->l);
		postorder(root->r);
		printf("%c",root->key);
	}
}

void main()
{
	tree *root=(tree*)malloc(sizeof(tree));
	char str[10000], opt;
	scanf("%c",&opt);
	while(opt != 't')
	{
		switch(opt)
		{
			case 'e': 
				scanf("%s",str);
				root = construct_tree(str);
				break;
			case 'i':
				inorder(root);
				printf("\n");
				break;
			case 'p':
				preorder(root);
				printf("\n");
				break;
			case 's':
				postorder(root);
				printf("\n");
				break;
		}
		scanf("%c", &opt);
	}
}
			
	
