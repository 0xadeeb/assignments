#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define nil ((void*)-1)

typedef struct set
{
    int key;
    int rank;
    struct set* parent;

}set;

typedef struct linkedList
{
    int key, weight;  
    struct linkedList* next;    
}ll;

typedef struct graph
{
    ll* head;
    ll* tail;
    struct graph* pred;

}graph;


typedef struct edge
{
    int u, v, w;
}edge;

typedef struct heap
{
    graph* vertex;
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

set* makeset(int key)
{
    set* node = (set*)malloc(sizeof(set));
    node->parent = node;
    node->key = key;
    node->rank = 0;

    return node;
}

int cmpFn(const void* a, const void* b)
{
    edge *x = (edge*)a, *y= (edge*)b;

    return x->w - y->w;
}


void insertH(set** forest, set* node)
{
    float h = (node->key)%256, i = -1;
    int pos;

    while(++i < 256)
    {
        pos = (int)(h + 0.5*i + 0.5*i*i)%256;
        if(forest[pos] == NULL || forest[pos] == nil)
        {
            forest[pos] = node;
            return;
        }    

        if(forest[pos]->key == node->key)
        {
            free(node);
            return;
        }    
    }

}

void linkH(set* x, set* y)
{
    if(x->rank >= y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
    }

    if(x->rank == y->rank)
        (x->rank)++;
}

set* findSet(set* x)
{
    if(x == x->parent)
        return x;

    x->parent = findSet(x->parent);
    return x->parent;
}

void Union(set*x, set* y)
{
    if(x == NULL || y == NULL)
        return;

    linkH(findSet(x),findSet(y));

}

set* search(set** forest, int x)
{
    float h = x%256, i = -1;
    int pos;

    while(++i < 256)
    {
        pos = (int)(h + 0.5*i + 0.5*i*i)%256;
        
        if(forest[pos] == NULL || forest[pos]->key == x)
            return forest[pos];

    }

    return NULL;

}

int KrushalsMST(edge* e, set** forest, int n)
{
    int weight = 0;

    for(int i = 0; i < n; i++)
    {
        set* x = search(forest,e[i].u), *y = search(forest,e[i].v);

        if(findSet(x) != findSet(y))
        {
            weight += e[i].w;
            Union(x,y);

        }
    }

    return weight;
}

void insertG(graph* b, ll* vertex)
{
    b->tail->next = vertex;
    b->tail = vertex;
}

void insertW(graph* g, int w)
{
    if(g->tail == NULL)
    {
        printf("Tail is NULL\n");
        return;
    }

    g->tail->weight = w;
    g->tail = g->tail->next;
}

ll* makeVertex(int key)
{
    ll* node = (ll*)malloc(sizeof(ll));
    node->key = key;
    node->next = NULL;
    return node;
}

heap* create(graph* vertex)
{
    heap* node = (heap*)malloc(sizeof(heap));
    node->vertex = vertex;
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

        if(h->min->vertex->head->weight > node->vertex->head->weight)
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

    if( (h->min == NULL) || (h2->min != NULL && h->min->vertex->head->weight > h2->min->vertex->head->weight) )
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
    //printf("y: %d, x: %d\n",y->right->vertex->key,y->left->vertex->key);
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

    if(x->child->vertex->head->weight > y->vertex->head->weight)
        x->child = y;
    
    x->degree = x->degree + 1;

}

void consolidate(fibHeap *h)
{
    int degree = maxDegree(h->n) + 1, d, w;
    heap** a = (heap**)malloc(degree * sizeof(heap*)), *x, *y, *t;
    x = h->min;
    //printf("vertex->key:%d, D: %d\n",x->vertex->key,x->degree);

    for(int i = 0; i< degree; i++)
        a[i] = NULL;

    do
    {
        if(x->vertex->head == NULL)
            break;
        //printf("vertex->key:%d, D: %d\n",x->vertex->key,x->degree);
        d = x->degree;
        while( a[d] != NULL)
        {
            y = a[d];
            if(y->vertex->head->weight < x->vertex->head->weight)
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

        if( a[i]->vertex->head->weight < h->min->vertex->head->weight)
            h->min = a[i];
    }

    free(a);
    
}

graph* extractMin(fibHeap* h)
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
    graph* vertex = t->vertex;
    //free(t);      

    return vertex;    

}

void printHeap(heap* h)
{
    if(h!= NULL)
    {
        heap* x = h;
        do
        {
            printf("%d ",x->vertex->head->key);
            if(x->child == x)
                x->child = NULL;
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
        if(x->vertex->head == NULL)
            return NULL;
        if(x->vertex->head->key == key)
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
            if(x->right->vertex->head->weight > x->left->vertex->head->weight)
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
    if(h->min == NULL || node == NULL || key > node->vertex->head->weight)
    {
        printf("-1\n");
        return;
    }

    node->vertex->head->weight = key;
    //printf("%d\n",node->vertex->head->weight);
    heap* p = node->parent;

    if(p != NULL && p->vertex->head->weight > node->vertex->head->weight)
    {
        cut(h, node, p);
        cascadingCut(h, p);
    }

    if(node->vertex->head->weight < h->min->vertex->head->weight)
        h->min = node;

}

void PrimsMST(fibHeap *q, graph** g)
{
    graph* u;
    int j;
    while(q->min != NULL)
    {
        u = extractMin(q);
        ll* v = u->head->next;
        while(v != NULL)
        {
            heap* h = findNode(q->min,v->key);
            if( h!=NULL && v->weight < h->vertex->head->weight)
            {
                g[v->key]->pred = u;
                decKey(q,h,v->weight);
            }
            
            v = v->next;
        }
        
    }

}

void main()
{
    char opt,k;
    int v, e = 0, t;
    scanf("%c%d",&opt,&v);
    scanf("%c",&k);

    switch (opt)
    {
        case 'a':
        {
            t = log2(v);
            set** forest = (set**)calloc(pow(2,t+1), sizeof(set*));
            edge *edg = (edge*)malloc(v*(v-1)*sizeof(edge));
            t = 0;

            for(int i = 0; i < v; i++)
            {
                int j = 0;
                while(scanf("%c",&k) && k != '\n')
                {
                    if(isdigit(k))
                        j = j * 10 + (int)(k - 48);

                    if(k == ' ')
                    {
                        if(i != j)
                        {
                            edg[e].u = i;
                            edg[e++].v = j;
                        }
                        j = 0;
                    }
                }  

                if(i != j)
                {
                    edg[e].u = i;
                    edg[e++].v = j;
                }

                insertH(forest, makeset(i));

            }

            edge *ed = (edge*)malloc(e * sizeof(edge));
            e = 0;

            for(int i = 0; i < v; i++)
            {
                int j=0, s = 0;
                while(scanf("%c",&k) && k != '\n')
                {
                    if(isdigit(k))
                    {
                        if( s == 0)
                            continue;
                        j = j * 10 + (int)(k - 48);
                    }

                    if(k == ' ')
                    {
                        s++;
                        if(s == 1)
                            continue;
                        if( edg[t].u > edg[t++].v)
                        {
                            ed[e].u = edg[t-1].u;
                            ed[e].v = edg[t-1].v;
                            ed[e++].w = j;
                        }
                        
                        j = 0;
                    }
                }

                if( edg[t].u > edg[t++].v)
                {
                    ed[e].u = edg[t-1].u;
                    ed[e].v = edg[t-1].v;
                    ed[e++].w = j;
                }

            }

            free(edg);
            ed = (edge*)realloc(ed, e * sizeof(edge));

            qsort(ed, e, sizeof(edge), cmpFn);

            int weight = KrushalsMST(ed,forest,e);
            printf("%d\n",weight);
            break;
        }

        case 'b':
        {
            graph** g = (graph**)malloc(v * sizeof(graph*));

            for(int i = 0; i < v; i++)
            {
                int j = 0;
                g[i] = (graph*)malloc(sizeof(graph));
                g[i]->head = makeVertex(i);
                g[i]->tail = g[i]->head;
                g[i]->pred = NULL;
                g[i]->head->weight = 1000001+i;

                while(scanf("%c",&k) && k != '\n')
                {
                    if(isdigit(k))
                        j = j * 10 + (int)(k - 48);

                    if(k == ' ')
                    {
                        if(i != j)
                            insertG(g[i],makeVertex(j));

                        j = 0;
                    }
                }  

                if(i != j)
                    insertG(g[i],makeVertex(j));

            }

            g[0]->head->weight = 0;

            for(int i = 0; i < v; i++)
            {
                int j=0, s = 0;
                g[i]->tail = g[i]->head->next;
                while(scanf("%c",&k) && k != '\n')
                {
                    if(isdigit(k))
                    {
                        if( s == 0)
                            continue;
                        j = j * 10 + (int)(k - 48);
                    }

                    if(k == ' ')
                    {
                        s++;
                        if(s == 1)
                            continue;
                        
                        insertW(g[i],j);

                        j = 0;
                    }
                }

                insertW(g[i],j);

            }
            
            fibHeap *h = makeHeap();

            for(int i = 0; i < v; i++)
                insert(h, create(g[i]));

            PrimsMST(h,g);
            int weight = 0;

            for(int i = 0; i< v; i++)
            {
                weight += g[i]->head->weight;
            }

            printf("%d\n",weight);


            break;
        }
    }


}


/*
a
7
0 1 5
1 0 2 6
2 1 3
3 2 4 6
4 3 5 6
5 0 4
6 1 3 4
0 28 10
1 28 16 14
2 16 12
3 12 22 18
4 22 25 24
5 10 25
6 14 18 24

*/