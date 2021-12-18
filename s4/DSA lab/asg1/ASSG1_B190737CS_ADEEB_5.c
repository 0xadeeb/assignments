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

float find(tree* root , int k , int *count)
{
	if(root!=NULL)
	{
		float res = find(root->left, k, count);
		if(res!=0.5)
			return res;
		(*count)++;
		if(*count == k)
			return root->key;
		res = find(root->right, k, count);
		if(res!=0.5)
			return res;
	}
	return 0.5;
}

int search_kth_smallest(tree* root , int k)
{
	int count = 0;
	return find(root, k, &count);
	
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
		
		printf("%d\n",search_kth_smallest(root,k));
	}
}		
		
