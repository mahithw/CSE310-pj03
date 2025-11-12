#ifndef STACK_H
#define STACK_H

#include "data_structures.h"

// imple int stack for path storage
typedef struct TAG_STACK {
    int capacity;
    int top;
    int* S;
} STACK;

typedef STACK* pSTACK;

pSTACK CreateStack(int capacity);
void Push(pSTACK S, int val);
int Pop(pSTACK S);
bool IsEmpty(pSTACK S);
void FreeStack(pSTACK S);

#endif
