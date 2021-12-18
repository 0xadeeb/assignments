#include<stdio.h>
#include<stdlib.h>

typedef struct bst
{
	int key;
	char child;
	struct bst *right, *left, *parent;
} bst;

bst* create_node(int key)
{
	bst * node = (bst*)malloc(sizeof(bst));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->child = 'x';
	node->key = key;
	return node;
}

bst* search(bst* root, int key)
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
void right(bst* root , bst* parent, bst* node)
{
	//printf("right\n");
	bst* chld = node->right;
	parent->right = chld;
	if(chld != NULL)
		chld->parent = parent;
	
}	
	
void left(bst* root , bst* parent, bst* node)
{
	//printf("left\n");
	bst* chld = node->left;
	parent->left = chld;
	if(chld != NULL)
		chld->parent = parent;
	
}
	
void transplant(bst* root, bst* del_pos, bst* replace, void (*child)(bst*,bst*,bst*))
{
	//printf("transplant\n");
	bst* parent = replace->parent,*left,*right;
	child(root, parent, replace);
	//printf("transplant after child\n");
	parent = del_pos->parent;
	left = del_pos->left;
	right = del_pos->right;
	if(parent!= NULL && del_pos->child == 'l')
		parent->left = replace;
	if(parent!= NULL && del_pos->child == 'r')
		parent->right = replace;
	if(left!=NULL)
		left->parent = replace;
	if(right!=NULL)
		right->parent = replace;		 
	replace->left = del_pos->left;
	replace->right = del_pos->right;
	replace->parent = del_pos->parent;
	replace->child = del_pos->child;
	
}

bst* tree_min(bst* node)
{
	if(node->left == NULL)
		return node;
	else
		return tree_min(node->left);
}

bst* tree_max(bst* node)
{
	if(node->right == NULL)
		return node;
	else
		return tree_max(node->right);
}		

void delete(bst** root, bst* node)
{
	
	if(node->right == NULL && node->left == NULL)
	{
		bst* parent = node->parent;
		if(parent == NULL)
		{
			free(node);
			*root = NULL;
		}	
		else if(node->child == 'l')
			parent->left = NULL;
		else 
			parent->right = NULL;
	}
	else
	{ 
		bst* replace;
		if(node->right!=NULL)
		{
			replace = tree_min(node->right);
			
			if( replace == node->right)
				transplant(*root, node, replace, right);
			else
				transplant(*root, node, replace, left);
			//	printf("delete\n");
		} 
		else 
		{
			replace = tree_max(node->left);
			if( replace == node->left)
				transplant(*root, node, replace, left);
			else
				transplant(*root, node, replace, right);
		}
		if( *root == node )
			*root = replace;
	}
	
	printf("%d\n",node->key);
	free(node);
}
			

void insert(bst* root, bst* node)
{
	 if(node->key > root->key)
	 {
	 	if(root->right == NULL)
	 	{
	 		node->child = 'r';
	 		root->right = node;
	 		node->parent = root;
	 	}
	 	else
	 		insert(root->right, node);
	 }
	 else if (node->key < root->key)
	 {
	 	if( root->left == NULL)
	 	{
	 		node->child = 'l';
	 		root->left = node;
	 		node->parent = root;
	 	}
	 	else 
	 		insert(root->left, node);
	 }
}

int tree_level(bst* root, bst* node,int level)
{
	if(root == NULL)
		return 0;
	
	if(node == root)
		return level;	
	
	int new_level= tree_level(root->left,node,level+1);
		
	if(new_level != 0)
		return new_level;
	
	new_level = tree_level(root->right,node,level+1);
		
	return new_level;
	
}

void inorder(bst* root)
{
	//printf("Hii\n");
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d ",root->key);
		inorder(root->right);
	}
	
}

void preorder(bst* root)
{
	if(root!=NULL)
	{
		printf("%d ",root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(bst* root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ",root->key);
	}
}

void find_p(bst* root, int key, bst** p)
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

void find_s(bst* root, int key, bst** s)
{	
	if(root != NULL)	
	{
		find_p(root->left,key,s);
		
		if(root->key > key)
		{
			if( *s == NULL || ( (*s)->key > root->key))
				*s = root;
		}
		
		
		find_p(root->right, key, s);
	}
	return;
}

void main()
{
	int key;
	char opt;
	bst *root=NULL, *p_s = NULL, *node;
	scanf("%c",&opt);	
	while(opt!='e')
	{
		switch(opt)
			{
				case 'a':scanf("%d",&key);
					node = create_node(key);
					if(root==NULL)
						root = node;
					else
						insert(root,node);
					break;
				case 'd':scanf("%d",&key);
					node = search(root, key);
					if(node!=NULL)
						delete(&root, node);
					else
						printf("-1\n");
					break;
				case 'i': inorder(root);
					printf("\n");
					break;
				case 'p': preorder(root);
					printf("\n");
					break;
				case 't': postorder(root);
					printf("\n");
					break;
				case 's': scanf("%d",&key);
					node = search(root, key);
					if(node!=NULL)
						printf("1\n");
					else
						printf("-1\n");
					break;
				case 'l': scanf("%d",&key);
					node = search(root, key);
					if(node!=NULL)
						printf("%d\n",tree_level(root,node,1));
					else
						printf("-1\n");
					break;
				case 'x': node = tree_max(root);
					printf("%d\n",node->key);
					break;
				case 'm': node = tree_min(root);
					printf("%d\n",node->key);
					break;
				case 'r': scanf("%d",&key);
					p_s = NULL;
					find_p(root,key,&p_s);
					if(p_s)
						printf("%d\n",p_s->key);
					else
						printf("-1\n");
					break;
				case 'u': scanf("%d",&key);
					p_s = NULL;
					find_s(root,key,&p_s);
					if(p_s)
						printf("%d\n",p_s->key);
					else
						printf("-1\n");
					
					break;
					
											
			}
		scanf("%c",&opt);
	}
	
}
	
