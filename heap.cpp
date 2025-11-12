#include "heap.h"
#include <cstdlib>

// create heap, size 0 initially
pHEAP CreateHeap(int capacity) {
    pHEAP heap = (pHEAP)calloc(1, sizeof(HEAP));
    heap->capacity = capacity;
    heap->size = 0;
    heap->H = (pELEMENT*)calloc(capacity + 1, sizeof(pELEMENT));
    return heap;
}

// standard min heap restore
void MinHeapify(pHEAP heap, int i) {
    int l = 2*i, r = 2*i+1, smallest = i;
    if (l <= heap->size && heap->H[l]->key < heap->H[smallest]->key)
        smallest = l;
    if (r <= heap->size && heap->H[r]->key < heap->H[smallest]->key)
        smallest = r;
    if (smallest != i) {
        pELEMENT tmp = heap->H[i];
        heap->H[i] = heap->H[smallest];
        heap->H[smallest] = tmp;
        heap->H[i]->position = i;
        heap->H[smallest]->position = smallest;
        MinHeapify(heap, smallest);
    }
}

// insert at bottom, bubble up
void Insert(pHEAP heap, pELEMENT v) {
    heap->size++;
    int i = heap->size;
    heap->H[i] = v;
    v->position = i;
    while (i > 1 && heap->H[i/2]->key > heap->H[i]->key) {
        pELEMENT tmp = heap->H[i];
        heap->H[i] = heap->H[i/2];
        heap->H[i/2] = tmp;
        heap->H[i]->position = i;
        heap->H[i/2]->position = i/2;
        i /= 2;
    }
}

// return min, fix heap
pELEMENT ExtractMin(pHEAP heap) {
    if (heap->size < 1) return NULL; // empty? return null
    pELEMENT min = heap->H[1];
    heap->H[1] = heap->H[heap->size];
    heap->H[1]->position = 1;
    heap->size--;
    MinHeapify(heap, 1);
    return min;
}

// update key and bubble up
// assumes new key is smaller
void DecreaseKey(pHEAP heap, int pos, double newKey) {
    heap->H[pos]->key = newKey;
    int i = pos;
    while (i > 1 && heap->H[i/2]->key > heap->H[i]->key) {
        pELEMENT tmp = heap->H[i];
        heap->H[i] = heap->H[i/2];
        heap->H[i/2] = tmp;
        heap->H[i]->position = i;
        heap->H[i/2]->position = i/2;
        i /= 2;
    }
}

// free heap memory
void FreeHeap(pHEAP heap) {
    if (!heap) return;
    free(heap->H);
    free(heap);
}
