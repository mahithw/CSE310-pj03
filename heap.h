#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

// reusing vertex as heap element
typedef VERTEX ELEMENT;
typedef ELEMENT* pELEMENT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT* H;  // 1-indexed heap array
} HEAP;

typedef HEAP* pHEAP;

// create heap with max size n
pHEAP CreateHeap(int capacity);
// insert new vertex pointer
void Insert(pHEAP heap, pELEMENT v);
// pop smallest key
pELEMENT ExtractMin(pHEAP heap);
// update key at position, move up if needed
void DecreaseKey(pHEAP heap, int pos, double newKey);
// normal heapify fix
void MinHeapify(pHEAP heap, int i);
// to free memory
void FreeHeap(pHEAP heap);

#endif
