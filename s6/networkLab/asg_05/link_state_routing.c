#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct path {
    int node;
    struct path *next;
} path;

typedef struct route {
    int dist;
    path *p;
} route;

int findMin(route *r, bool *visited, int n) {
    int min = INT_MAX, minIdx;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && r[i].dist < min) {
            minIdx = i;
            min = r[i].dist;
        }
    }
    return minIdx;
}

void updatePath(route *r, int v, int u) {
    path *t = r[v].p->next, *n, *curr;
    while (t) {
        n = t->next;
        free(t);
        t = n;
    }
    t = r[u].p->next, curr = r[v].p;
    while (t) {
        n = (path *)malloc(sizeof(path));
        n->node = t->node;
        curr->next = n;
        curr = n;
        t = t->next;
    }
    n = (path *)malloc(sizeof(path));
    n->node = v;
    n->next = NULL;
    curr->next = n;
}

void printPath(path *p) {
    if (p == NULL)
        return;
    path *temp = p, *n;
    while (temp->next) {
        printf("%d->", temp->node + 1);
        n = temp->next;
        free(temp);
        temp = n;
    }
    printf("%d", temp->node + 1);
    free(temp);
}

void dijkstra(int **g, int idx, int n) {
    route *r = (route *)malloc(n * sizeof(route));
    bool *visited = (bool *)calloc(n, sizeof(bool));
    for (int i = 0; i < n; i++) {
        r[i].dist = i == idx ? 0 : INT_MAX;
        r[i].p = (path *)malloc(sizeof(path));
        r[i].p->node = idx;
        r[i].p->next = NULL;
    }

    for (int i = 0; i < n; i++) {
        int u = findMin(r, visited, n);
        visited[u] = true;
        for (int v = 0; v < n; v++) {
            if (v == u || g[u][v] == INT_MAX)
                continue;
            if (r[u].dist + g[u][v] < r[v].dist) {
                r[v].dist = r[u].dist + g[u][v];
                updatePath(r, v, u);
            }
        }
    }

    r[idx].p->next = (path *)malloc(sizeof(path));
    r[idx].p->next->node = idx;
    r[idx].p->next->next = NULL;

    printf("\n");
    printf("Routing table at node %d\n", idx + 1);
    for (int i = 0; i < n; i++) {
        printPath(r[i].p);
        printf("\t\t%d\n", r[i].dist);
    }

    free(r);
}

int main() {
    int n, m, u, v, w;
    scanf("%d%d", &n, &m);
    int **g = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        g[i] = (int *)malloc(n * sizeof(int));
        wmemset(g[i], INT_MAX, n);
        g[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g[u - 1][v - 1] = w;
        g[v - 1][u - 1] = w;
    }

    for (int i = 0; i < n; i++) {
        dijkstra(g, i, n);
    }

    return 0;
}
