#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include "heap.h"
#include "stack.h"

class Graph {
public:
    int n;
    pVERTEX* V;
    pNODE* ADJ;

    int lastSource;
    int lastDest;
    bool wasPair;

    Graph(int n);
    void AddEdge(int u, int v, int idx, double w, bool toFront);
    void PrintADJ();
    void DijkstraSinglePair(int s, int t);
    void DijkstraSingleSource(int s);
    void PrintPath(int s, int t, pSTACK stack);
    void PrintLength(int s, int t);
    void ResetVertices();
    ~Graph();
};

#endif
