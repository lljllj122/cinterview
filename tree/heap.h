#ifndef _heap_h
#define _heap_h
#include <stdlib.h>
#include <string.h>

typedef int Heap_elem;
typedef int (*Heap_cmp)(const Heap_elem, const Heap_elem);
typedef enum {
    MIN,
    MAX
} Heap_type;

typedef struct Heap {
    int size;
    int cap;
    Heap_elem *elems;
    Heap_cmp cmp;
    Heap_type type;
} Heap;


Heap *Heap_create(int *data, const int size, const int capacity, Heap_cmp cmp, Heap_type t);
Heap *Heap_build(int *data, const int size, Heap_type t);
void Heap_destroy(Heap *h);
int Heap_empty(const Heap *h);
int Heap_size(const Heap *h);

int Heap_change(Heap *h, int pos, Heap_elem key);
int Heap_push(Heap *h, Heap_elem key);
void Heap_pop(Heap *h);
Heap_elem Heap_top(const Heap *h);

#endif
