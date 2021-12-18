#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct bst
{
	int model_number,price;
	char child, model_name[25];
	struct bst *right, *left, *parent;
} bst;

bst* create_node(int model_number, char* model_name, int price)
{
	bst * node = (bst*)malloc(sizeof(bst));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->child = 'x';
	node->model_number = model_number;
	strcpy(node->model_name, model_name);
	node->price = price;	
	return node;
}

bst* search(bst* root, int model_number)
{
	if (root == NULL || root->model_number == model_number)
		return root;
	else
	{
		if(model_number < root->model_number)
			search(root->left, model_number);
		else
			search(root->right, model_number);
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
		return tree_min(node->right);
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
	printf("%d %s %d\n",node->model_number,node->model_name,node->price);
	free(node);
}
			

void insert(bst* root, bst* node)
{
	 if(node->model_number > root->model_number)
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
	 else if (node->model_number < root->model_number)
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
		printf("%d %s %d\n",root->model_number,root->model_name,root->price);
		inorder(root->right);
	}
	
}

void preorder(bst* root)
{
	if(root!=NULL)
	{
		printf("%d %s %d\n",root->model_number,root->model_name,root->price);
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
		printf("%d %s %d\n",root->model_number,root->model_name,root->price);
	}
}	 

void main()
{
	int model_number,price;
	char opt, model_name[25];
	bst *root=NULL, *node;
	scanf("%c",&opt);	
	while(opt!='e')
	{
		switch(opt)
			{
				case 'a':scanf("%d%s%d",&model_number,model_name,&price);
					node = create_node(model_number,model_name,price);
					if(root==NULL)
						root = node;
					else
						insert(root,node);
					break;
				case 'd':scanf("%d",&model_number);
					node = search(root, model_number);
					if(node!=NULL)
						delete(&root, node);
					else
						printf("-1\n");
					break;
				case 'i': inorder(root);
					break;
				case 'p': preorder(root);
					break;
				case 't': postorder(root);
					break;
				case 'm': scanf("%d%d",&model_number,&price);
					node = search(root, model_number);
					if(node!=NULL)
						node->price = price;
					break;
				case 's': scanf("%d",&model_number);
					node = search(root, model_number);
					if(node!=NULL)
						printf("%d %s %d\n",node->model_number,node->model_name,node->price);
					else
						printf("-1\n");
											
			}
		scanf("%c",&opt);
	}
	
}
	
	
	
/*
a 2000 abv 250000
a 1990 xca 130000
a 2014 vta 500000
a 2019 ctwq 450000
a 1999 fgha 550000
a 2020 ghja 980000
*/
