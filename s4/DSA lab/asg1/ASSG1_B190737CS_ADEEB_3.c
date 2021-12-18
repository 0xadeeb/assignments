#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

typedef struct tree
{
	int key;
	struct tree* right;
	struct tree* left;
	struct tree* parent;
} tree;

tree* create(int key)
{
	tree* node = malloc(sizeof(tree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent  = NULL;
	return node;
}

tree* build_tree(char* t, int *pos, tree* parent)
{
	
	int key = 0, len = strlen(t);
	tree* node = NULL;
	bool neg = false;
	
	if(t[*pos] == '-')
	{
		neg = true;
		(*pos)++;
	}
	
	if(isdigit(t[*pos]))
	{
		while(*pos<len && isdigit(t[*pos]))
			key = key*10 + (t[(*pos)++] - 48);
		
		if(neg)
			key*=-1;
		
		node = create(key);
		node->parent = parent;
		
	}
	
	if(*pos< len && t[*pos] == '(')
	{
		*pos = *pos+1;
		node->left = build_tree(t, pos , node);
	}
	
	if(*pos < len && t[*pos] == ')')
		{ (*pos)++; return node; }
	
	if(*pos< len && t[*pos] == '(')
	{
		*pos = *pos+1;
		node->right = build_tree(t, pos, node);
	}
	
	if(*pos < len && t[*pos] == ')')
		{ (*pos)++; return node; }
	
	return node;
}

void sum_bst(tree* root, int *sum, bool* bst)
{
	if(root!= NULL && *bst)
	{
		tree *left = root->left, *right = root->right;
		if(left != NULL && left->key > root->key)
				*bst = false;
		
		if(right!=NULL && right->key < root->key)
				*bst = false;
				
		sum_bst(left, sum, bst);
		sum_bst(right, sum, bst);
		
		(*sum)+=root->key;
	}
}
			

void search_sum(tree* root, int k, int *sum)
{
	if(root!=NULL)
	{
		int tot_sum = 0;
		bool bst = true;
		sum_bst(root, &tot_sum, &bst);
		if(bst && tot_sum == k)
			(*sum)++;
		search_sum(root->left, k , sum);
		search_sum(root->right, k, sum);
	}
}
		

void main()
{
	tree* root, *node,*temp;
	char *t = (char*)malloc(2048*sizeof(char)),c;
	int k,sum = 0, i = -1;
	
	while(scanf("%c",&c) && c  != '\n')
	{
		if(c == ' ')
			continue;
		if(i<0)
		{
			i++;
			continue;
		}
		else
			t[i++] = c;
	}
	
	t[--i] = '\0';
	
	if(i!=0)
	{
	
		t = (char*)realloc(t, sizeof(char)* i);
		i =0;
		scanf("%d",&k);
		root = build_tree(t,&i,NULL);
		
		search_sum(root,k,&sum);
		
		if(sum)
			printf("%d\n",sum);
		else
			printf("-1\n");
	}
	else
		printf("-1\n");
}


/*( 257 ( 108 ( 79 ( -45 ( -152 ( ) ( ) ) ( -12 ( ) ( ) ) ) ( 54 ( -48 ( ) ( ) ) ( 54 ( ) ( ) ) ) ) ( 162 ( 87 ( 90 ( ) ( ) ) ( 178 ( ) ( ) ) ) ( 200 ( ) ( ) ) ) ) ( 843 ( 592 ( 372 ( ) ( ) ) ( 678 ( ) ( ) ) ) ( 1011 ( 927 ( ) ( ) ) ( 2020 ( ) ( ) ) ) ) ) 

( 31 ( 22 ( 20 ( 12 ) ( ) ) ( 27 ( ) ( ) ) ) ( 42 ( 39 ( ) ( ) ) ( ) ) ) */
