#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct heap
{
    int key;
    int degree;
    struct heap* child;
    struct heap* sibling;
    struct heap* parent;
}heap;

heap* create(int key)
{
    heap* node = (heap*)malloc(sizeof(heap));
    node->key = key;
    node->degree = 0;
    node->child = NULL;
    node->parent = NULL;
    node->sibling = NULL;

    return node;
}

void printLevel(heap* h, int level, int cur_level)
{
    if(h!=NULL)
    {
        if(cur_level != level)
        {
            while(h!=NULL)
            {
                printLevel(h->child, level, cur_level+1);
                h = h->sibling;
            }
        }

        else
        {
            while(h!=NULL)
            {
                //printf("l: %d k: ",cur_level);
                printf("%d ",h->key);
                h = h->sibling;
            }
        }
    }

}

void printTree(heap* h, int degree)
{
    int level = 1;

    while(level <= degree)
    {
        printLevel(h,level,1);
        level++;
    }
}

void printHeap(heap* H)
{
    while(H!=NULL)
    {
        printf("%d ", H->key);
        printTree(H->child, H->degree);
        H = H->sibling;
    }

}

int findMin(heap* h)
{
    if(h == NULL)
        return -1000006;

    int min = h->key;
    h = h->sibling;

    while(h!=NULL)
    {
        if(h->key<min)
            min = h->key;
        
        h = h->sibling;
    }

    return min;
}

heap* heap_merge(heap* h1, heap* h2)
{
    if(h1 == NULL || h2 == NULL)
    {
        if(h1 != NULL)
            return h1;
        else
            return h2;
    }

    heap* h = NULL, *temp;

    while(h1 != NULL && h2 != NULL)
    {
        if(h1->degree < h2->degree)
        {
            if(h == NULL)
            {
                h = h1;
                temp = h;
                h1 = h1->sibling;
                continue;
            }
            
            temp->sibling = h1;
            h1 = h1->sibling;
            temp = temp->sibling;
            continue;     

        }

        else
        {
            if(h == NULL)
            {
                h = h2;
                temp = h;
                h2 = h2->sibling;
                continue;
            }
            
            temp->sibling = h2;
            h2 = h2->sibling;
            temp = temp->sibling;
            continue;
        }
    }

    if(h1 == NULL)
        temp->sibling = h2;
    else
        temp->sibling = h1;

    return h;
}

void link(heap* x, heap* y)
{
    y->parent = x;
    y->sibling = x->child;
    x->child = y;
    x->degree = x->degree +1;
}

heap* heap_union(heap* h1, heap* h2)
{
    heap* x = heap_merge(h1,h2);
    heap *head = x;
     
    if(x == NULL)
        return x;

    heap *prev = NULL, *next = head->sibling;
    

    while(next != NULL)
    {
        if(next->degree != x->degree || (next->sibling!=NULL && next->degree == x->degree && x->degree == next->sibling->degree))
        {
            prev = x;
            x = next;
            next = x->sibling;

            continue;            
        }

        if(next->key < x->key)
        {
            if(prev != NULL)
                prev->sibling = next;
            else
                head = next;

            link(next, x);

            x = next;
            next = x->sibling;
            continue;

        }

        else
        {
            x->sibling = next->sibling;
            link(x, next);
            next = x->sibling;
            continue;
        }
    }
   
    return head;


}

heap* findNode(heap* h, int key)
{
    if(h != NULL)
    {
        if(h->key == key)
            return h;
        
        else
        {
            heap* node = findNode(h->child,key);
            if(node == NULL)
                return findNode(h->sibling,key);

            else
                return node;
        }
    }

    return NULL;
}

heap* decKey(heap* h, int z, int key)
{
    heap* x = findNode(h,z), *y;
    if(x == NULL)
    {   
        printf("-1\n");
        return NULL;
    }

    if(x->key < key)
    {   
        printf("-1\n");
        return NULL;
    }  
    
    x->key -= key;
    y = x->parent;
    printf("%d\n",x->key);

    while(y != NULL && x->key < y->key)
    {
        int temp = x->key;
        x->key = y->key;
        y->key = temp;

        x = y;
        y = x->parent;
    }

    return x;
    
}

heap* bubbleUp(heap* h, int z)
{
    heap* x = findNode(h,z), *y;
    if(x == NULL)
    {   
        printf("-1\n");
        return NULL;
    }
    
    y = x->parent;

    while(y != NULL)
    {
        int temp = x->key;
        x->key = y->key;
        y->key = temp;

        x = y;
        y = x->parent;
    }

    return x;
    
}

void insert_inFront(heap** h, heap* node)
{
    node->parent = NULL;
    node->sibling = *h;
    *h = node;

}

heap* delete_h(heap* h, int key)
{
    if(h == NULL)
    {
        printf("-1\n");
        return NULL;
    }
    
    heap* t = bubbleUp(h,key), *h1 = NULL, *prv = h; 
    
    if(t== NULL)
        return h;

    printf("%d\n",t->key); 
    heap* child, *node = t->child, *sib = t->sibling;

    while(node!=NULL)
    {
        child = node;
        node = node->sibling;
        insert_inFront(&h1,child);
    }

    if(t != h)
    {
        while(prv->sibling != t)
            prv = prv->sibling;
        
        prv->sibling = t->sibling;
    }

    else
        return heap_union(sib, h1);

    free(t);
    // printHeap(h1);
    // printf("\n");

    return heap_union(h,h1);

}

void main()
{
    char opt;
    int key, x;
    heap *H = NULL, *node;

    while(scanf("%c",&opt) && opt != 'e')
        switch (opt)
        {
            case 'i':
                scanf("%d",&key);
                H = heap_union(H,create(key));
                break;
            
            case 'd':
                scanf("%d",&key);
                H = delete_h(H, key);
                break;

            case 'm':
                key = findMin(H);
                if(key != -1000006)
                    printf("%d\n",key);
                break;
            
            case 'x':
                H = delete_h(H, findMin(H));
                break;

            case 'p':
                printHeap(H);
                printf("\n");
                break;
            
            case 'r':
                scanf("%d %d",&x, &key);
                decKey(H,x,key);
                break;
            
            default:
                break;
        }
}

/*

i 10
i 20
i 35
i 40
i 50
p
m
x
p
r 50 4
p
r 70 5
e


i 17
i 38
i 42
i 2
i 5
i 7
i 15
i 16
p
x
p
e

i 45
i 36
i 82
i 15
i 59
i 86
i 95
p
m
r 45 40
m
p
e

i 17
i 24
i 15
i 36
p
r 24 15
p
i 24
i 3
p
e

*/

