#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct tree
{
    int key;
    int height;
    int count;
    struct tree* right;
    struct tree* left;
}tree;

tree* create_tree(int key)
{
    tree* node = (tree*)malloc(sizeof(tree));
    node->key = key;
    node->height = 0;
    node->count = 1;
    node->right = NULL;
    node->left = NULL;
    return node;
}

int max(int a, int b)
{
    if(a>b)
        return a;
    
    else
        return b;
}

int height(tree* node)
{
    if(node == NULL)
        return -1;

    else
        return node->height;
}

int getBalance(tree* node)
{
    return height(node->left) - height(node->right);
}

bool isAvl(tree* node)
{
    int bf = getBalance(node);

    if(bf < -1 || bf > 1)
        return false;
    
    else
        return true;
}

void ll(tree** node)
{
    tree* t = *node;
    tree* p = t->left;
    t->left = p->right;
    p->right = t;
    t->height = 1 + max(height(t->left),height(t->right));
    p->height = 1 + max(height(p->left),height(p->right));
    *node = p;
}

void rr(tree** node)
{
    tree *t = *node;
    tree* p = t->right;
    t->right = p->left;
    p->left = t;
    t->height = 1 + max(height(t->left),height(t->right));
    p->height = 1 + max(height(p->left),height(p->right));
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

tree* insert(tree* root, tree* node)
{
    if(root == NULL)
        return node;

    else if(node->key < root->key)
        root->left = insert(root->left, node);

    else if(node->key > root->key)
        root->right = insert(root->right, node);

    else   
    {
        (root->count)++;
        free(node); 
        return root;
    }

    root->height = 1 + max(height(root->right),height(root->left));

    int bf = getBalance(root);
    
    if(isAvl(root) == false)
    {
        //printf("%d %d\n",root->key, bf);
        if(bf>1)
        {
            if(node->key < (root->left)->key)
                ll(&root);
            else
                lr(&root);
        }

        if(bf<-1)
        {
            if(node->key > (root->right)->key)
                rr(&root);
            
            else
                rl(&root);
        }
    }

    return root;
}

void print(tree* root)
{   
    if(root != NULL)
    {
        print(root->left);
        for(int i = 0; i < root->count; i++)
            printf("%d ",root->key);
        print(root->right);
    }
}

void main()
{
    tree* root = NULL, *node;
    int n, key;

    scanf("%d",&n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d",&key);
        node = create_tree(key);
        root = insert(root, node);
    }

    print(root);
    printf("\n");

}


