#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct linkedList
{
    int key;
    struct  linkedList* next;    
}ll;

ll* makeVertex(int key)
{
    ll* node = (ll*)malloc(sizeof(ll));
    node->key = key;
    node->next = NULL;

    return node;
}

void insert(ll** tail, ll* vertex)
{
    ll* t = *tail;
    t->next = vertex;
    *tail = vertex;
}

void main()
{
    int n, key;
    scanf("%d",&n);
    ll** list = (ll**)malloc(n*sizeof(ll*)), *vertex, *tail;

    for(int i = 0; i < n; i++)
    {
        list[i] = makeVertex(i);
        tail = list[i];
        for(int j = 0; j < n; j++)
        {
            scanf("%d",&key);
            if(key == 1)
            {
                vertex = makeVertex(j);
                insert(&tail, vertex);
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        vertex = list[i];
        while(vertex != NULL)
        {
            printf("%d ",vertex->key);
            vertex = vertex->next;
        }
        printf("\n");
    }


}
    