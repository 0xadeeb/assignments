#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct tree
{
    int key;
    char colour;
    struct tree* right;
    struct tree* left;
}tree;

tree* create_node(int key)
{
    tree* node = (tree*)malloc(sizeof(tree));
    node->key = key;
    node->colour = 'R';
    node->right = NULL;
    node->left = NULL;

    return node;
}

void ll(tree** node)
{
    tree* t = *node;
    tree* p = t->left;
    t->left = p->right;
    p->right = t;
    *node = p;
}

void rr(tree** node)
{
    tree *t = *node;
    tree* p = t->right;
    t->right = p->left;
    p->left = t;
    *node = p;
}

void lr(tree** node)
{   
    tree* p = (*node)->left;
    rr(&p);
    (*node)->left = p;
    ll(node);
}

void rl(tree** node)
{
    tree* p = (*node)->right;
    
    ll(&p);
    (*node)->right = p;
    rr(node);
}

char colour(tree* node)
{
    if(node == NULL)
        return 'B';
   
    else
        return node->colour;
}

void colour_flip(tree* root)
{
    if(root == NULL)
        return;
    root->colour = 'R';
    root->left->colour = 'B';
    root->right->colour = 'B';
}

void modify_left(tree** root)
{
    tree *r = *root;
    
    if(colour(r->left) == 'B')
        return;

    else if (colour(r->left->left) == 'R' || colour(r->left->right) == 'R')
    {
        if(colour(r->right) == 'R')
        {
            colour_flip(r);
            return;
        }

        if(colour(r->right) == 'B')
        {
            if(colour(r->left->right) == 'R')
                lr(root);

            else
                ll(root);

            r = *root;
            r->colour = 'B';
            r->right->colour = 'R';
            return;
        }

        else
            return;
    }
}

void modify_right(tree** root)
{
    tree *r = *root;
    
    if(colour(r->right) == 'B')
        return;

    else if (colour(r->right->left) == 'R' || colour(r->right->right) == 'R')
    {
        if(colour(r->left) == 'R')
        {
            colour_flip(r);
            return;
        }

        if(colour(r->left) == 'B')
        {
            if(colour(r->right->left) == 'R')
                rl(root);

            else
                rr(root);

            r = *root;
            r->colour = 'B';
            r->left->colour = 'R';
            return;
        }

        else
            return;
    }
}

tree* insert(tree* root, tree* node)
{
    if(root == NULL)
        return node;

    else if( root->key > node->key)
    {
        root->left = insert(root->left, node);
        modify_left(&root);
        return root;
    }

    else if(root->key < node->key)
    {
        root->right = insert(root->right, node);
        modify_right(&root);
        return root;
    }

    else
        return root;
}

void print(tree* root)
{
	printf("( ");
	if(root!=NULL)
	{
		printf("%d %c ",root->key, root->colour);
		print(root->left);
		print(root->right);
	}
	printf(") ");
}

void main()
{
    int key;
    tree* root = NULL;

    while(scanf("%d",&key))
    {
        root = insert(root, create_node(key));
        root->colour = 'B';
        print(root);
        printf("\n");
    }
}