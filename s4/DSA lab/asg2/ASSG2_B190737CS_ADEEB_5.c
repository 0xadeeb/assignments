#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct tree
{
	int key;
	struct tree* left;
	struct tree* right;
} tree;


tree* create(int key)
{
	tree* node = (tree*)malloc(sizeof(tree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

tree* build_tree(char* t, int *pos)
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
		
	}
	
	if(*pos< len && t[*pos] == '(')
	{
		*pos = *pos+1;
		node->left = build_tree(t, pos);
	}
	
	if(*pos < len && t[*pos] == ')')
		{ (*pos)++; return node; }
	
	if(*pos< len && t[*pos] == '(')
	{
		*pos = *pos+1;
		node->right = build_tree(t, pos);
	}
	
	if(*pos < len && t[*pos] == ')')
		{ (*pos)++; return node; }
	
	return node;
}

float find_sm(tree* root , int k , int *count)
{
	if(root!=NULL)
	{
		float res = find_sm(root->left, k, count);
		if(res!=0.5)
			return res;
		(*count)++;
		if(*count == k)
			return root->key;
		res = find_sm(root->right, k, count);
		if(res!=0.5)
			return res;
	}
	return 0.5;
}

int search_kth_smallest(tree* root , int k)
{
	int count = 0;
	return (int)find_sm(root, k, &count);
	
}

float find_l(tree* root , int k , int *count)
{
	if(root!=NULL)
	{
		float res = find_l(root->right, k, count);
		if(res!=0.5)
			return res;
		(*count)++;
		if(*count == k)
			return root->key;
		res = find_l(root->left, k, count);
		if(res!=0.5)
			return res;
	}
	return 0.5;
}

void find_p(tree* root, int key, tree** p)
{	
	if(root != NULL)	
	{
		find_p(root->left,key,p);
		
		if(root->key < key)
		{
			if( *p == NULL || ( (*p)->key < root->key))
				*p = root;
		}
		
		
		find_p(root->right, key, p);
	}
	return;
}

void find_s(tree* root, int key, tree** s)
{	
	if(root != NULL)	
	{
		find_s(root->left,key,s);
		
		if(root->key > key && *s == NULL)
				*s = root;
		
		find_s(root->right, key, s);
	}
	return;
}

tree* search(tree* root, int key)
{
	if (root == NULL || root->key == key)
		return root;
	else
	{
		if(key < root->key)
			search(root->left, key);
		else
			search(root->right, key);
	}
}

int search_kth_largest(tree* root , int k)
{
	int count = 0;
	return (int)find_l(root, k, &count);
	
}

void inorder(tree* root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d ",root->key);
		inorder(root->right);
	}
	
}

void main()
{
	int key,sum = 0, i = -1;
	char opt;
	tree *root=NULL, *node, *p_s;
	char *t = (char*)malloc(2048*sizeof(char)),c;
	
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
		scanf("%d",&key);
		root = build_tree(t,&i);
		scanf("%c",&opt);	
		while(opt!='e')
		{
			switch(opt)
				{
					case 'i': inorder(root);
						printf("\n");
						break;
		
			
					case 'r': 
						scanf("%d",&key);
						node = search(root,key);
						if(node == NULL)
							printf("-1\n");
						else
						{
							p_s = NULL;
							find_p(root,node->key,&p_s);
							if(p_s)
								printf("%d\n",p_s->key);
							else
								printf("-1\n");
						}
						break;	
						
					case 'u': 
						scanf("%d",&key);
						node = search(root,key);
						if(node == NULL)
							printf("-1\n");
						
						else
						{
							p_s = NULL;
							find_s(root,node->key,&p_s);
							if(p_s)
								printf("%d\n",p_s->key);
							else
								printf("-1\n");
						}
						
						break;
						
					case 'l': 
						scanf("%d",&key);
						printf("%d\n",search_kth_largest(root,key));
						break;
					case 's':
						scanf("%d",&key);
						printf("%d\n",search_kth_smallest(root,key));
						break;
												
				}
			scanf("%c",&opt);
		}
	}
	
}

