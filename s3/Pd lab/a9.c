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
	 
	bst* replace, *parent = node->parent;
	if(node->right!=NULL)
	{
		replace = tree_min(node->right);
		
		if( replace == node->right)
			transplant(*root, node, replace, right);
		else
			transplant(*root, node, replace, left);
		
	} 
	else if( node->left!=NULL)
	{
		replace = tree_max(node->left);
		if( replace == node->left)
			transplant(*root, node, replace, left);
		else
			transplant(*root, node, replace, right);
	}
	else
	{
		if(parent == NULL)
			replace = NULL;
				
		else if(node->child == 'l')
			parent->left = NULL;
		else 
			parent->right = NULL;
	}
	
	if( *root == node )
			*root = replace;
	
	
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

void main()
{
	int key;
	char opt;
	bst *root=NULL, *node;
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
				case 'm': node = tree_min(root); 
					printf("Min: %d\n",node->key);
					node= tree_max(root);
					printf("Max: %d\n", node->key);
					
											
			}
		scanf("%c",&opt);
	}
	
}
	
