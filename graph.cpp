#include "graph.h"
#include <cstdio>
#include <cstdlib>

Graph::Graph(int n) {
    this->n = n;
    V = (pVERTEX*)calloc(n+1, sizeof(pVERTEX));
    ADJ = (pNODE*)calloc(n+1, sizeof(pNODE));
    for (int i=1;i<=n;i++) {
        V[i] = (pVERTEX)calloc(1, sizeof(VERTEX));
        V[i]->index = i;
    }
}

void Graph::AddEdge(int u, int v, int idx, double w, bool toFront) {
    pNODE node = (pNODE)calloc(1, sizeof(NODE));
    node->u = u;
    node->v = v;
    node->index = idx;
    node->w = w;

    if (toFront) {
        node->next = ADJ[u];
        ADJ[u] = node;
    } else {
        if (!ADJ[u]) ADJ[u] = node;
        else {
            pNODE t = ADJ[u];
            while (t->next) t = t->next;
            t->next = node;
        }
    }
}

void Graph::PrintADJ() {
    for (int i=1;i<=n;i++) {
        printf("ADJ[%d]:", i);
        pNODE t = ADJ[i];
        while (t) {
            printf("-->[%d %d: %4.2lf]", t->u, t->v, t->w);
            t = t->next;
        }
        printf("\n");
    }
}

void Graph::ResetVertices() {
    for (int i=1;i<=n;i++) {
        V[i]->key = DBL_MAX;
        V[i]->pi = 0;
        V[i]->color = WHITE;
        V[i]->position = 0;
    }
}

void Graph::DijkstraSinglePair(int s, int t) {
    ResetVertices();
    pHEAP heap = CreateHeap(n);
    V[s]->key = 0;
    V[s]->color = GRAY;
    Insert(heap, V[s]);

    while (heap->size > 0) {
        pVERTEX u = ExtractMin(heap);
        if (u->index == t) break;

        pNODE adj = ADJ[u->index];
        while (adj) {
            pVERTEX v = V[adj->v];
            double newKey = u->key + adj->w;
            if (v->color == WHITE) {
                v->color = GRAY;
                v->key = newKey;
                v->pi = u->index;
                Insert(heap, v);
            } else if (v->color == GRAY && newKey < v->key) {
                v->key = newKey;
                v->pi = u->index;
                DecreaseKey(heap, v->position, newKey);
            }
            adj = adj->next;
        }
        u->color = BLACK;
    }
    FreeHeap(heap);
}

void Graph::DijkstraSingleSource(int s) {
    DijkstraSinglePair(s, -1);
}

void Graph::PrintPath(int s, int t, pSTACK stack) {
    if (V[t]->key == DBL_MAX) {
        printf("There is no path from %d to %d.\n", s, t);
        return;
    }

    printf("The shortest path from %d to %d is:\n", s, t);

    int cur = t;
    while (cur != 0) {
        Push(stack, cur);
        cur = V[cur]->pi;
    }

    while (!IsEmpty(stack)) {
        int v = Pop(stack);
        printf("[%d:%8.2lf]", v, V[v]->key);  // FIXED spacing here
        if (!IsEmpty(stack)) printf("-->");
    }
    printf(".\n");
}

void Graph::PrintLength(int s, int t) {
    if (V[t]->key == DBL_MAX) {
        printf("There is no path from %d to %d.\n", s, t);
    } else {
        printf("The length of the shortest path from %d to %d is:%8.2lf\n",
            s, t, V[t]->key);  // FIXED spacing here
    }
}

Graph::~Graph() {
    for (int i=1;i<=n;i++) {
        free(V[i]);
        pNODE cur = ADJ[i];
        while (cur) {
            pNODE nxt = cur->next;
            free(cur);
            cur = nxt;
        }
    }
    free(V);
    free(ADJ);
}
