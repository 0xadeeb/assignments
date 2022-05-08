#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int dist, next;
} node;

typedef struct link {
    int u, v, w;
} edge;

typedef struct router {
    int v, e;
    edge *edges;
} graph;

void bellmanFord(int idx, graph *g) {
    node *d = (node *)malloc(g->v * sizeof(node));
    for (int i = 0; i < g->v; i++) {
        d[i].dist = i == idx ? 0 : INT_MAX;
        d[i].next = i == idx ? idx : -1;
    }

    for (int i = 0; i < g->v; i++) {
        for (int j = 0; j < g->e; j++) {
            if (d[g->edges[j].u].dist == INT_MAX)
                continue;
            if (d[g->edges[j].v].dist > g->edges[j].w + d[g->edges[j].u].dist) {
                d[g->edges[j].v].dist = g->edges[j].w + d[g->edges[j].u].dist;
                if (g->edges[j].u == idx) {
                    d[g->edges[j].v].next = g->edges[j].v;
                } else {
                    d[g->edges[j].v].next = d[g->edges[j].u].next;
                }
            }
        }
    }

    printf("Routing table at node %d\n", idx + 1);
    for (int i = 0; i < g->v; i++) {
        printf("%d %d %d\n", i + 1, d[i].next + 1, d[i].dist);
    }
    printf("\n");

    free(d);
}

int main() {
    int u, v, w;
    graph *g = (graph *)malloc(sizeof(graph));
    scanf("%d%d", &(g->v), &(g->e));
    g->e *= 2;
    g->edges = (edge *)malloc(g->e * sizeof(edge));
    for (int i = 0; i < g->e; i += 2) {
        scanf("%d%d%d", &u, &v, &w);
        g->edges[i].u = u - 1;
        g->edges[i].v = v - 1;
        g->edges[i].w = w;
        g->edges[i + 1].v = u - 1;
        g->edges[i + 1].u = v - 1;
        g->edges[i + 1].w = w;
    }

    for (int i = 0; i < g->v; i++) {
        bellmanFord(i, g);
    }

    return 0;
}
