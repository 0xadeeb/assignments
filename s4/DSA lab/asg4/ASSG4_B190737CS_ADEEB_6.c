#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct heap
{
    int key;
    int degree;
    bool mark;
    struct heap* parent;
    struct heap* right;
    struct heap* left;
    struct heap* child; 

}heap;

typedef struct fibHeap
{
    heap* min;
    int n;
}fibHeap;

heap* create(int key)
{
    heap* node = (heap*)malloc(sizeof(heap));
    node->key = key;
    node->child = NULL;
    node->parent = NULL;
    node->right = node;
    node->left = node;
    node->mark = false;
    node->degree = 0;

    return node;
}

fibHeap* makeHeap()
{
    fibHeap *H = (fibHeap*)malloc(sizeof(fibHeap));
    H->min = NULL;
    H->n = 0;

    return H;
}

void insert(fibHeap* h, heap* node)
{
    if(h->min == NULL)
    {
       h->min = node;
       h->n = 1; 
    }

    else
    {
        heap* left = h->min->left;
        h->min->left = node;
        node->right = h->min;
        left->right = node;
        node->left = left;

        if(h->min->key > node->key)
            h->min = node;

        h->n = h->n + 1;

    }


}

fibHeap* heapUnion(fibHeap* h1, fibHeap* h2)
{
    fibHeap* h = makeHeap();
    h->min = h1->min;

    heap* left = h->min->left, *t = h2->min->left, *right = h->min->right;
    right->left = h2->min->left;
    h->min->right = h2->min;
    h2->min->left = h->min;
    t->right = right;

    if( (h->min == NULL) || (h2->min != NULL && h->min->key > h2->min->key) )
        h->min = h2->min;

    h->n = h1->n + h2->n;

    free(h1);
    free(h2);
    
    return h; 

}

int maxDegree(int n)
{
    double d = 2.078087 * log(n);

    return (int)(d);
}

void link(fibHeap* h, heap* y, heap* x)
{
    //printf("y: %d, x: %d\n",y->right->key,y->left->key);
    y->right->left = y->left;
    y->left->right = y->right;

    if(x->right == x)
        h->min = x;

    y->left = y;
    y->right = y;
    y->parent = x;

    if(x->child == NULL)
        x->child = y;

    y->right = x->child;
    y->left = x->child->left;
    x->child->left->right = y;
    x->child->left = y;

    if(x->child->key > y->key)
        x->child = y;
    
    x->degree = x->degree + 1;

}

void consolidate(fibHeap *h)
{
    int degree = maxDegree(h->n) + 1, d, w;
    heap** a = (heap**)malloc(degree * sizeof(heap*)), *x, *y, *t;
    x = h->min;
    //printf("key:%d, D: %d\n",x->key,x->degree);
    //scanf("%d",&w);

    for(int i = 0; i< degree; i++)
        a[i] = NULL;

    do
    {
        //printf("key:%d, D: %d\n",x->key,x->degree);
        //scanf("%d",&w);
        d = x->degree;
        while( a[d] != NULL)
        {
            y = a[d];
            if(y->key < x->key)
            {
                t = x;
                x = y;
                y = t;
            }

            if(y == h->min)
                h->min = x;
            
            link(h, y, x);

            if(y->right == x)
                h->min = x;

            a[d] = NULL;
            d++;
        }

        a[d] = x;
        x = x->right;
        
    } while (x != h->min);

    h->min = NULL;

    for(int i = 0; i < degree; i++)
    if(a[i] != NULL)
    {
        if(h->min == NULL)
        {
            a[i]->left = a[i];
            a[i]->right = a[i];
        }

        if(h->min == NULL)
            h->min = a[i];
        
        else
        {
            heap* left = h->min->left;
            left->right = a[i];
            a[i]->left = left;
            a[i]->right = h->min;
            h->min->left = a[i];

        }

        if( a[i]->key < h->min->key)
            h->min = a[i];
    }

    free(a);
    
}

void extractMin(fibHeap* h)
{

    heap* t = h->min, *next = NULL, *x = NULL;

    if( t->child != NULL)
    {
        x = t->child;
        do
        {
            next = x->right;
            x->right = t;
            x->left = t->left;
            t->left->right = x;
            t->left = x;
            x->parent = NULL;
            x = next;

        }while(x != t->child);

    }

    t->left->right = t->right;
    t->right->left = t->left;
    
    if(h->n == 1)
        h->min = NULL;
    
    else
    {
        h->min = t->right;
        consolidate(h);
    }

    h->n = h->n -1; 
    free(t);       
    
    

}

void printHeap(heap* h)
{
    if(h!= NULL)
    {
        heap* x = h;
        do
        {
            printf("(key:%d, deg:%d)",x->key, x->degree);
            printHeap(x->child);
            x = x->right;

        } while (x != h);        

    }
}

heap* findNode(heap* node, int key)
{
    if(node == NULL)
        return NULL;

    heap* x = node, *p = NULL;

    do
    {
        if(x->key == key)
            return x;
        if(x->child == x)
            x->child = NULL;
        p = findNode(x->child, key);
        if(p != NULL)
            return p;

        x = x->right;

    } while (x != node);

    return NULL;

}

void cut(fibHeap* h, heap* x, heap* p)
{
    
    x->left->right = x->right;
    x->right->left = x->left;

    if(x == p->child)
    {
        if(x->right == x)
            p->child = NULL;

        else
        {
            if(x->right->key > x->left->key)
                p->child = x->left;

            else    
                p->child = x->right;
        }
    }

    p->degree = p->degree - 1;
    x->left = x;
    x->right = x;
    x->parent = NULL;
    insert(h,x);

    x->mark = false;  


}

void cascadingCut(fibHeap* h, heap* x)
{
    if(x->parent != NULL)
    {
        if(x->mark == false)
            x->mark = true;
        
        else
        {
            cut(h, x, x->parent);
            cascadingCut(h,x->parent);
        }
    }

}


void decKey(fibHeap* h, heap* node, int key)
{
    if(h->min == NULL || node == NULL || key > node->key)
    {
        printf("-1\n");
        return;
    }

    node->key = key;
    printf("%d\n",node->key);
    heap* p = node->parent;

    if(p != NULL && p->key > node->key)
    {
        cut(h, node, p);
        cascadingCut(h, p);
    }

    if(node->key < h->min->key)
        h->min = node;

}

void bubbleUp(fibHeap* h, heap* node)
{
    node->key = -1000005;

    heap* p = node->parent;

    if(p != NULL && p->key > node->key)
    {
        cut(h, node, p);
        cascadingCut(h, p);
    }

    h->min = node;

}

void deleteNode(fibHeap* h, int key)
{
    if(h->min == NULL)
    {
        printf("-1\n");
        return;
    }    
    
    heap* node = findNode(h->min,key);
    if(node == NULL)
    {
        printf("-1\n");
        return;
    }    
        
    printf("%d\n",node->key);
    bubbleUp(h,node);
    extractMin(h);

}

void main()
{
    char opt;
    int key, x;
    fibHeap *H = makeHeap();
    heap* t =  NULL;

    while(scanf("%c",&opt) && opt != 'e')
        switch (opt)
        {
            case 'i':
                scanf("%d",&key);
                insert(H,create(key));
                break;
            
            case 'd':
                scanf("%d",&key);
                deleteNode(H, key);
                break;

            case 'm':
                if(H->min == NULL)
                    printf("-1\n");
                else
                    printf("%d\n",H->min->key);

                break;
            
            case 'x':
                if(H->min == NULL)
                    printf("-1\n");
                else    
                {
                    printf("%d\n",H->min->key);
                    extractMin(H);
                }
                break;

            case 'p':
                printHeap(H->min);
                printf("\n");
                break;
            
            case 'r':
                scanf("%d %d",&x, &key);
                t = findNode(H->min, x);
                decKey(H,t,key);
                break;
            
            default:
                break;
        }

}