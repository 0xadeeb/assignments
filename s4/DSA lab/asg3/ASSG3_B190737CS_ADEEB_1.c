#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct tree
{
    int key;
    int height;
    struct tree* right;
    struct tree* left;
}tree;

tree* create_tree(int key)
{
    tree* node = (tree*)malloc(sizeof(tree));
    node->key = key;
    node->height = 0;
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
        return root;

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

tree* tree_min(tree* node)
{
    if(node->left == NULL)
        return node;

    (node->height)--;

    if((node->left)->left== NULL)
    {
        tree* t = node->left;
        node->left = node->left->right;
        return t;
    }    

    return tree_min(node->left);
}

tree* delete_node(tree* root, int key, bool* shorter)
{
    char del;

    if(root == NULL)
    {
        printf("FALSE\n");
        return NULL;
    }
    
    int bf_p = getBalance(root), bf_q;
    
    if(root->key > key)
    {    
        del = 'l';
        if(root->right != NULL)
            bf_q = getBalance(root->right);
        root->left = delete_node(root->left, key, shorter);
    }
    
    else if(root->key < key)
    {
        del = 'r';
        if(root->left != NULL)
            bf_q = getBalance(root->left);
        root->right = delete_node(root->right, key, shorter);
    }

    else
    {        
        if(root->right == NULL && root->left == NULL)
        {
            printf("%d\n",root->key);
            free(root);
            return NULL;
        }

        else if(root->right != NULL && root->left == NULL)
        {
            tree* r = root->right;
            printf("%d\n",root->key);
            free(root);
            return r;       
        }

        else if(root->left != NULL && root->right == NULL)
        {
            tree* l = root->left;
            printf("%d\n",root->key);
            free(root);
            return l;   

        }

        else
        {
            tree *s = tree_min(root->right);
            printf("%d\n",root->key);
            del = 'r';
            bf_q = getBalance(root->left);
            if( s != root->right)
                s->right = root->right;
            s->left = root->left;
            free(root);
            root = s;
        }
    }

    root->height = 1 + max(height(root->left),height(root->right));
    if(*shorter)
    {
        //printf("%d bf:%d\n",root->key, bf_p);
        if(bf_p == 0)
        {
            *shorter = false;
            return root;
        }

        if((bf_p == -1 && del == 'r') || (bf_p == 1 && del == 'l'))
            return root;

        else
        {
            if(del == 'l')
            {
                if(bf_q == 0)
                {
                    rr(&root);
                    *shorter = false;
                }

                else if(bf_q == bf_p)
                    rr(&root);

                else
                    rl(&root);
            }

            if(del == 'r')
            {
                
                if(bf_q == 0)
                {
                    ll(&root);
                    *shorter = false;
                }

                else if(bf_q == bf_p)
                    ll(&root);

                else
                    lr(&root);
            }
            
        }

    }
    
    return root;
        
}

tree* search(tree* root, int key)
{
    if(root == NULL)
        return root;

    if(key < root->key)
        return search(root->left, key);

    if(key > root->key)
        return search(root->right, key);

    if(key == root->key)
        return root;
}

void print(tree* root)
{
	printf("( ");
	if(root!=NULL)
	{
		printf("%d ",root->key);
		print(root->left);
		print(root->right);
	}
	printf(") ");
}

void main()
{
    tree* root = NULL, *node;
    int key;
    char opt;
    bool shorter;

    while(scanf("%c",&opt) && opt != 'e')
    {
        switch(opt)
        {
            case 'i': 
                scanf("%d",&key);
                root = insert(root,create_tree(key));
                break;

            case 'd':
                scanf("%d",&key);
                shorter = true;
                root = delete_node(root,key, &shorter);
                
                break;
            
            case 's':
                scanf("%d", &key);
                if(search(root, key) != NULL)
                    printf("TRUE\n");
                else 
                    printf("FALSE\n");

                break;

            case 'b':
                scanf("%d", &key);
                node = search(root,key);

                if(node != NULL)
                    printf("%d\n",getBalance(node));
                
                else    
                    printf("FALSE\n");
                
                break;

            case 'p':
                print(root);
                printf("\n");
                break;

        }
    }
        
                     
}

/*

i 20 i 4 i 26 i 3 i 9 i 21 i 30 i 2 i 7 i 11


*/