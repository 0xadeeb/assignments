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

typedef struct queue
{
	tree* t;
	struct queue* next;
} queue;

tree* create(int key)
{
	tree* node = malloc(sizeof(tree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent  = NULL;
	return node;
}

queue* create_q(tree* t)
{
	queue* node = (queue*)malloc(sizeof(queue));
	node->t = t;
	node->next = NULL;
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
		
void inorder(tree* root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d ",root->key);
		inorder(root->right);
	}
	
}

void preorder(tree* root)
{
	
	if(root!=NULL)
	{
		printf("%d ",root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(tree* root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ",root->key);
	}
}

tree* find_node(tree* root, int element , int *level, bool* found)
{
	if(root!= NULL)
	{
		tree* node;
		if(root->key == element)
		{	
			*found = true;
			return root;
		}
		if(root->key != element)
		{
			if(!(*found))
				(*level)++;
			node = find_node(root->left,element,level,found);
		}
		if( node == NULL)
		{
			if(!(*found))
				(*level)++;
			node = find_node(root->right,element,level,found);
		}
		if(!(*found))
			(*level)--;
		return node;
	}
	if(!(*found))
		(*level)--;
	return NULL;
}

void find_cousins(queue** head,queue **tail,tree* root, tree* parent, int level, int* cur_lvl)
{

	if(parent == NULL)
		return;
	if(*cur_lvl <= level && root!=NULL)
	{

		if(level == *cur_lvl && root != parent)
		{

			queue* node;
			if(root->left != NULL)
			{
				node = create_q(root->left);
				if(*head == NULL)
				{
					*head = node;
					*tail = node;
				}
				else
				{
					queue* temp = *tail;
					temp->next = node;
					*tail = node;
				}
			}
			if(root->right != NULL)
			{

				node = create_q(root->right);
				if(*head == NULL)
				{
					*head = node;
					*tail = node;
				}
				else
				{
					queue* temp = *tail;
					temp->next = node;
					*tail = node;
				}
			}
			(*cur_lvl)--;
			return;
		}
		else
		{
			(*cur_lvl)++;
			find_cousins(head,tail,root->left,parent,level,cur_lvl);
			(*cur_lvl)++;
			find_cousins(head,tail,root->right,parent,level,cur_lvl);
		}
	}
	(*cur_lvl)--;
}
	

void main()
{
	tree* root, *node,*temp;
	queue* head = NULL, *tail = NULL;
	bool found = false;
	char *t = (char*)malloc(2048*sizeof(char)),c;
	int element, pos = 0 , i = -1;
	
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
		
		scanf("%d",&element);
		root = build_tree(t,&pos,NULL);
		
		i =0;
		node = find_node(root, element,&i,&found);
		
		int lvl=0;
		if(node!=NULL)
		{
			temp = node->parent;
			find_cousins(&head,&tail,root,node->parent,i-1,&lvl);
			if(head==NULL)
				printf("-1");
			while(head!=NULL)
			{
				
				queue* cur = head;
				tree* t = cur->t;
				
				head = head->next;
				printf("%d ",t->key);
				free(cur);
			}
			printf("\n");
		}
		else
			printf("-1\n");
			
		
	}
	else
		printf("-1\n");
	
}



