#include "stack.h"
#include <cstdlib>

// make stack, top -1 means empty
pSTACK CreateStack(int capacity) {
    pSTACK s = (pSTACK)calloc(1, sizeof(STACK));
    s->capacity = capacity;
    s->top = -1;
    s->S = (int*)calloc(capacity, sizeof(int));
    return s;
}

// no overflow check
void Push(pSTACK S, int val) {
    if (S->top < S->capacity - 1)
        S->S[++S->top] = val;
    // else ignore push lol
}

// return top or -1 if empty
int Pop(pSTACK S) {
    if (S->top >= 0)
        return S->S[S->top--];
    return -1;
}

bool IsEmpty(pSTACK S) {
    return S->top == -1;
}

void FreeStack(pSTACK S) {
    if (!S) return;
    free(S->S);
    free(S);
}
