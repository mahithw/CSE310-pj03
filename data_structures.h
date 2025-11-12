#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <cfloat>

// colors for dijkstr
enum COLOR {WHITE, GRAY, BLACK};

// vertex struct, holds dist, parent, heap position etc
typedef struct TAG_VERTEX {
    int index;      // node number
    COLOR color;    // visited state
    double key;     // distance from source
    int pi;         // parent, 0 means none i think?
    int position;   // position in heap array
} VERTEX;

typedef VERTEX* pVERTEX;

// linked list node for adjacency list
// naming is weird but matches prof slides
typedef struct TAG_NODE {
    int index;   // edge index from file
    int u;       // from
    int v;       // to
    double w;    // weight
    TAG_NODE* next;
} NODE;

typedef NODE* pNODE;

#endif
