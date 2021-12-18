#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define nil ((void*)-1)

typedef struct set1
{
    int key;
    struct set1* parent;

}set1;

typedef struct set2
{
    int key;
    int rank;
    struct set2* parent;

}set2;

set1* makeset1(int key)
{
    set1* node = (set1*)malloc(sizeof(set1));
    node->parent = node;
    node->key = key;

    return node;
}

set2* makeset2(int key)
{
    set2* node = (set2*)malloc(sizeof(set2));
    node->parent = node;
    node->key = key;
    node->rank = 0;

    return node;
}

set1* insert1(set1** forest, set1* node)
{
    float h = (node->key)%256, i = -1;
    int pos;

    while(++i < 256)
    {
        pos = (int)(h + 0.5*i + 0.5*i*i)%256;
        if(forest[pos] == NULL || forest[pos] == nil)
        {
            forest[pos] = node;
            return node;
        }    

        if(forest[pos]->key == node->key)
        {
            free(node);
            return NULL;
        }
    }

}

void insert2(set2** forest, set2* node)
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

void link1(set1* x, set1* y)
{
    printf("%d ",x->key);
    y->parent = x;
}

void link2(set2* x, set2* y)
{
    if(x->rank >= y->rank)
    {
        printf("%d ",x->key);
        y->parent = x;
    }
    else
    {
        printf("%d ",y->key);
        x->parent = y;
    }

    if(x->rank == y->rank)
        (x->rank)++;
}

set1* findSet00(set1* x, int* count)
{
    (*count)++;
    while(x != x->parent)
    {
        (*count)++;
        x = x->parent;
    }

    return x;
}

set1* findSet01(set1* x, int* count)
{
    (*count)++;
    if(x == x->parent)
        return x;

    x->parent = findSet01(x->parent,count);
    return x->parent;
}

set2* findSet10(set2* x, int* count)
{
    (*count)++;
    while(x != x->parent)
    {
        (*count)++;
        x = x->parent;
    }

    return x;
}

set2* findSet11(set2* x, int* count)
{
    (*count)++;
    if(x == x->parent)
        return x;

    x->parent = findSet11(x->parent,count);
    return x->parent;
}

void union00(set1*x,set1* y, int* count)
{
    if(x == NULL || y == NULL)
    {
        printf("-1\n");
        return;
    }

    link1(findSet00(x,count),findSet00(y,count));

}

void union01(set1*x,set1* y, int* count)
{
    if(x == NULL || y == NULL)
    {
        printf("-1\n");
        return;
    }

    link1(findSet01(x,count),findSet01(y,count));

}

void union10(set2*x, set2* y, int* count)
{
    if(x == NULL || y == NULL)
    {
        printf("-1\n");
        return;
    }

    link2(findSet10(x,count),findSet10(y,count));

}

void union11(set2*x, set2* y, int* count)
{
    if(x == NULL || y == NULL)
    {
        printf("-1\n");
        return;
    }

    link2(findSet11(x,count),findSet11(y,count));
    printf("\n");

}

set1* search1(set1** forest, int x)
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

set2* search2(set2** forest, int x)
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


void main()
{
    char opt;
    int y, x, c00 =0, c01= 0, c10= 0, c11 = 0;
    set1** forest00 = (set1**)calloc(256, sizeof(set1*)),**forest01 = (set1**)calloc(256, sizeof(set1*)), *node1;
    set2** forest10 = (set2**)calloc(256, sizeof(set2*)),**forest11 = (set2**)calloc(256, sizeof(set2*)), *node2;

    while(scanf("%c",&opt))
        switch (opt)
        {
            case 'm':
                scanf("%d",&y);
                node1 = insert1(forest00,makeset1(y));
                insert2(forest10,makeset2(y));
                insert1(forest01,makeset1(y));
                insert2(forest11,makeset2(y));
                if(node1 == NULL)
                {
                    printf("-1\n");
                    break;
                }
                printf("%d\n",y);
                break;

            case 'u':
                scanf("%d%d",&x,&y);
                union00(search1(forest00,x),search1(forest00,y),&c00);
                union10(search2(forest10,x),search2(forest10,y),&c10);
                union01(search1(forest01,x),search1(forest01,y),&c01);
                union11(search2(forest11,x),search2(forest11,y),&c11);
                break;

            case 'f':
                scanf("%d",&x);
                node1 = search1(forest00,x);
                node2 = search2(forest10,x);
                if(node2 == NULL)
                {
                    printf("-1\n");
                    break;
                }
                node1 = findSet00(node1,&c00);
                node2 = findSet10(node2,&c10);
                printf("%d ",node1->key);
                printf("%d ",node2->key);
                node1 = search1(forest01,x);
                node2 = search2(forest11,x);
                node1 = findSet01(node1,&c01);
                node2 = findSet11(node2,&c11);
                printf("%d ",node1->key);
                printf("%d\n",node2->key);
                break;

            case 's':
                printf("%d %d %d %d\n",c00, c10, c01, c11);
                exit(0);         

        }



}
