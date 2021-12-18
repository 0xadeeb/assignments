#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct set*
{
	int key;
	struct set* parent;
	struct set* left;
	struct set* right;
	char child;
} set;

typedef struct collection
{
	set* root;
	struct collection *nxt;
	
} collection; 

set* create_node(int key)
{
	set * node = (set*)malloc(sizeof(set));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->child = 'x';
	node->key = key;
	return node;
}

void insert(set* root, set* node)
{
	if(node->key < root->key)
	{
		if(root->left == NULL)
		{
			root->left = node;
			node->parent = root;
			node->child = 'l';
		}
		else 
			insert(root->left, node);
	}
	else
	{
		if(root->right == NULL)
		{
			root->right = node;
			node->parent = root;
			node->child = 'r';
		}
		else
			insert(root->right, node);
	}
}

void insert_set(collection **c, set* s)
{
	node->nxt = *c;
	*c = node;
}

set* find(set* root, int key)
{
	if(root == NULL || root->key == key)
		return root;
	
	else 
	{
		if( root->key > key)
			return find(root->left, key);
		else
			return find(root->right, key);
	}
}


collection* find_set(collection *c, int k)
{
	collection *temp = c, *node=NULL;
	while(temp ! = NULL)
	{
		node = find(temp->root,k);
		if(node != NULL)
			return temp;
		temp = temp->nxt;
	}
	return NULL;
		
}


set* tree_min(set* node)
{
	if(node->left == NULL)
		return node;
	else
		return tree_min(node->left);
}

set* tree_max(set* node)
{
	if(node->right == NULL)
		return node;
	else
		return tree_min(node->right);
}		

void delete(set* node)
{
	if( node!= NULL)
	{
		delete(node->left);
		delete(node->right);
		free(node);
	}
	
}

void delete_set(collection** head, collection* node)
{
	collection* temp = *head;
	
	if(node == *head)
		*head = temp->nxt;
		
	else
	{
		while(temp != NULL && temp->nxt!=node)
			temp = temp->nxt;
		
		temp->nxt = node->nxt;	
	}
	
	delete(node->root);
	free(node);
}
		
void merge_set(collection** head, collection* t1, collection* t2)
{
	collection *temp = *head;
	set *t1_set = t1->root, *t2_set->root;
	
	if(t2 == *head)
		*head = temp->nxt;
	
	
	
	
	
