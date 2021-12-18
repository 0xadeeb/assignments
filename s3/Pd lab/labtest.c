#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>

typedef struct tree
{
	char key;
	struct tree *r, *l;
} tree;

typedef struct tree_stack
{
	struct tree *parent;
	struct tree_stack *nxt;
} tree_stack;


typedef struct stack
{
	char key;
	struct stack* nxt;
} stack;
	

int priority(char x)
{
	if(x == '*' || x == '/')
		return 2;
	if(x == '(')
		return 0;
	else
		return 1;
}

void push(stack** top, char x)
{
	stack* node= (stack*)malloc(sizeof(stack));
	node->key = x;
	node->nxt = *top;
	*top = node;
}

char pop(stack **top)
{
	char x;
	stack *temp = *top;
	*top = temp->nxt;
	x = temp->key;
	free(temp);
	return x;
}		

char *to_post(char *str)
{
	int j=0;
	stack* top=NULL;
	char *res = (char*)malloc(strlen(str)*sizeof(char));
	for(int i=0; str[i]!=';'; i++)
	{
		if(isalpha(str[i]))
			res[j++] =str[i];
		
		else if(str[i]=='(')
			push(&top,'(');
			
		else if ( str[i] == ')')
		{
			while(top->key != '(')
				res[j++] =pop(&top);
			pop(&top);
		}
		else
		{
			while(top!=NULL&&priority(str[i])<=priority(top->key))
				res[j++] =pop(&top);
			push(&top,str[i]);		
		}	
	}
	
	while( top != NULL)
		res[j++] =pop(&top);
	res[j]='\0';
	return res;
}

tree* pop_tree(tree_stack **top)
{
	tree* root;
	tree_stack *temp = *(top);
	*top = temp->nxt;
	root = temp->parent;
	free(temp);
	return root;
}


void push_tree(tree_stack** top, tree* subtree)
{
	tree_stack* node= (tree_stack*)malloc(sizeof(tree_stack));
	node->parent = subtree;
	node->nxt = *top;
	*top = node;
}


tree* create_tree(char s,tree* l, tree* r)
{
	tree *subtree = (tree*)malloc(sizeof(tree));
	subtree->key = s;
	subtree->r = r;
	subtree->l = l;
	return subtree;
}

tree* construct_tree(char *str1)
{
	tree_stack* top = NULL;
	
	tree *subtree = NULL, *r = (tree*)malloc(sizeof(tree)), *l= (tree*)malloc(sizeof(tree)), *variable, *root;
	char *str = to_post(str1);
	char u[20];
	printf("%d",strlen(str));
	scanf("%s",u);
	for( int i=0; i< strlen(str); i++)
	{	
		if(isalpha(str[i]))
		{
			
			subtree = create_tree(str[i],NULL,NULL);
			
			push_tree(&top , subtree);
			
		}
		else 
		{
			
			r = pop_tree(&top);
			l = pop_tree(&top);
			subtree = create_tree(str[i],l,r);
			push_tree(&top, subtree);
		}
	}
	
	
	
	return pop_tree(&top);
	
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

void main()
{
	char* exp = (char*)malloc(100000*sizeof(char));
	scanf("%s",exp);
	exp = (char*)realloc(exp, strlen(exp)*sizeof(char));
	char* s= (char*)malloc((strlen(exp)-2)*sizeof(char));
	
	for(int i=2; i<=strlen(exp); i++)
		s[i-2] = exp[i];
	
	tree* expression = construct_tree(s), *variable, *root;
	variable = create_tree(*exp,NULL,NULL);
	root = create_tree('=',variable,expression);
	inorder(root);
}
	
