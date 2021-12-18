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
	while(node->right != NULL)
		node = node->right;
	return node;
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
	
	//printf("%d\n",node->key);
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

bst* combine1(bst* t1, int k, bst* t2)
{
	bst* root = create_node(k);
	root->left = t1;
	root->right = t2;
	if(t1!=NULL)
	{
		t1->parent = root;
		t1->child = 'l';
	}
	if(t2!=NULL)
	{
		t2->parent = root;
		t2->child = 'r';
	}
	return root;
}

bst* combine2(bst* t1, bst* t2)
{
	bst* root, *t1_max;
	int k ;
	if(t1!=NULL)
	{	
		t1_max= tree_max(t1);
		k= t1_max->key;
		delete(&t1, t1_max);
		root = combine1(t1, k , t2);
	}
	else 
		root=t2;
	return root;
}

void main()
{
	int key;
	char c;
	bst *t1=NULL,*t2=NULL, *node, *root;
	int n1,n2;
	scanf("%d%d",&n1,&n2);
	for(int i=0; i<n1; i++)
	{
		scanf("%d",&key);
		node = create_node(key);
		if(t1==NULL)
			t1 = node;
		else
			insert(t1,node);	
	}
	
	for(int i=0; i<n2; i++)
	{
		scanf("%d",&key);
		node = create_node(key);
		if(t2==NULL)
			t2 = node;
		else
			insert(t2,node);	
	}
	
	root= combine2(t1,t2);
	t1 = NULL;
	t2 = NULL;
	inorder(root);	
	printf("\n");
		
		
	
}
