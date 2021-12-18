#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct linkedList
{
    int key;
    struct linkedList* next;    
}ll;

typedef struct queue
{
    ll* vertex;
    struct queue* nxt;
}queue;

typedef struct graph
{
    ll* head;
    ll* tail;
    int distance;
    int start_t;
    int end_t;
    struct linkedList* pred;
    char colour;

}graph;

ll* makeVertex(int key)
{
    ll* node = (ll*)malloc(sizeof(ll));
    node->key = key;
    node->next = NULL;
    return node;
}

queue* makeQueue(ll* vertex)
{
    queue* node = (queue*)malloc(sizeof(queue));
    node->vertex = vertex;
    node->nxt = NULL;
    
    return node;
}

void insert(graph* b, ll* vertex)
{
    b->tail->next = vertex;
    b->tail = vertex;
}

void insertQ(queue** head, queue** tail, ll* vertex)
{
    if(vertex == NULL)
        return;

    queue* v = makeQueue(vertex);

    if(*head == NULL)
    {
        *head = v;
        *tail = v;
        return;
    }

    (*tail)->nxt = v;
    *tail = v;

}

int delQ(queue** head, queue** tail)
{
    if(*head == NULL)
        return -1000000;

    int vertex = (*head)->vertex->key;
    queue* t= *head;

    if(*head == *tail)
    {
        *head = NULL;
        *tail = NULL;
    }

    else
        *head = t->nxt;
    
    free(t);
    return vertex;


}

void BFS(graph **g, ll* s)
{
    queue *head = NULL, *tail = NULL;
    g[s->key]->colour = 'g';
    insertQ(&head, &tail, s);
    char c;
    while(head != NULL)
    {
        int u = delQ(&head,&tail);
        ll* t = g[u]->head;
        printf("%d ",g[u]->head->key);
        while(t!= NULL)
        {
            if(g[t->key]->colour == 'w')
            {
                g[t->key]->colour = 'g';
                g[t->key]->distance = g[u]->distance + 1;
                g[t->key]->pred = g[u]->head;
                insertQ(&head,&tail,g[t->key]->head);
            }
            t = t->next;
        }

        g[u]->colour = 'b';

    }

}

void DFSvisit(graph** g, int u, int time)
{
    printf("%d ",u);
    g[u]->colour = 'g';
    g[u]->start_t = ++time;

    ll* t = g[u]->head;
    while(t!= NULL)
    {
        if(g[t->key]->colour == 'w')
        {
            g[t->key]->pred = g[u]->head;
            DFSvisit(g,g[t->key]->head->key,time);
        }
        t = t->next;
    }

    g[u]->colour = 'b';
    g[u]->end_t = ++time;


}

void DFS(graph** g, ll* s, int v)
{
    int time = 0;

    for(int i = 0; i<v; i++)
        if(g[i]->colour == 'w')
            DFSvisit(g, g[i]->head->key, time);    

}

void main()
{
    int v, e, x, y;

    scanf("%d%d",&v,&e);
    graph** list = (graph**)malloc(v * sizeof(graph*));
    ll* vertex;

    for(int i = 0; i < v; i++)
    {
        list[i] = (graph*)malloc(sizeof(graph));
        list[i]->head = makeVertex(i);
        list[i]->tail = list[i]->head;
        list[i]->colour = 'w';
        list[i]->pred = NULL;
        list[i]->distance = 0;
    }

    for(int i = 0; i < e; i++)
    {
        scanf("%d%d",&x,&y);
        insert(list[x],makeVertex(y));        
    }

    scanf("%d",&x);

    BFS(list, list[x]->head);
    printf("\n");
    for(int i = 0; i< v; i++)
        list[i]->colour = 'w';

    DFSvisit(list, x, 0);
    printf("\n");

}


/*
8 14
0 1
0 2
0 3
0 4
1 0
1 6
2 1
3 1
3 5
4 7
5 6
6 2
6 4
1 3
*/