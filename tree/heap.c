#include "../lib/dbg.h"
#include "heap.h"
#include <limits.h>

static int cmp_max(const int a, const int b)
{
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

static int cmp_min(const int a, const int b)
{
    if (a > b) return -1;
    else if (a < b) return 1;
    else return 0;
}

Heap *Heap_create(int *data, const int size, const int capacity, Heap_cmp cmp, Heap_type t)
{
    Heap *h = calloc(1, sizeof(Heap));
    check_mem(h);

    h->size = size;
    h->cap = capacity;
    h->type = t;
    h->cmp = (cmp == NULL) ? (t == MIN ? cmp_min : cmp_max) : cmp;

    h->elems = (Heap_elem *)malloc(capacity * sizeof(Heap_elem));
    check_mem(h->elems);

    if (data) {
        memcpy(h->elems, data, size * sizeof(Heap_elem));
    }

    return h;
error:
    if (h) Heap_destroy(h); 
    return NULL;
}

static inline void Heapify(Heap *h, int i) 
{
    i = i + 1;
    int l = 2 * i;
    int r = 2 * i + 1;
    
    int ret;
    int minormax;
    ret = h->cmp(h->elems[l-1], h->elems[i-1]);
    minormax = (l <= h->size && ret == 1) ? l : i;
    ret = h->cmp(h->elems[r-1], h->elems[minormax-1]);
    minormax = (r <= h->size && ret == 1) ? r : minormax;

    if (minormax != i) {
        h->elems[i-1] = h->elems[i-1] ^ h->elems[minormax-1];
        h->elems[minormax-1] = h->elems[i-1] ^ h->elems[minormax-1];
        h->elems[i-1] = h->elems[i-1] ^ h->elems[minormax-1];
        Heapify(h, minormax);
    }
}

Heap *Heap_build(int *data, const int size, Heap_type t)
{
    Heap *h = Heap_create(data, size, size * 1, NULL, t);
    h->size = size;
   
    if (data && size > 0) {
        for (int i = (size - 1)/2; i >= 0; i--) {
            Heapify(h, i);
        }
    }
    return h;
}

void Heap_destroy(Heap *h)
{
    if (h) {
        if (h->elems) free(h->elems);
        free(h);
    }
}

int Heap_empty(const Heap *h) 
{
    return h->size == 0;
}

int Heap_size(const Heap *h) 
{
    return h->size;
}

int Heap_change(Heap *h, int pos, Heap_elem key)
{
    if (h->cmp(key, h->elems[pos]) == -1) {
        log_err("Key is wrong");
        goto error;
    }

    h->elems[pos] = key;

    int p = (pos + 1) / 2 - 1;

    while (pos > 0 && h->cmp(h->elems[p], h->elems[pos]) == -1) {
        h->elems[pos] = h->elems[p] ^ h->elems[pos];
        h->elems[p] = h->elems[p] ^ h->elems[pos];
        h->elems[pos] = h->elems[p] ^ h->elems[pos];
        pos = p;
        p = (pos + 1) / 2 - 1;
    }

    return 1;
error:
    return -1;
}

int Heap_push(Heap *h, Heap_elem key)
{
    if (h->size == h->cap) {
        Heap_elem *buffer = realloc(h->elems, h->cap * 2 * sizeof(Heap_elem));
        h->elems = buffer;
        h->cap *= 2;
    }

    h->elems[h->size] = INT_MIN;
    h->size++;

    return Heap_change(h, h->size - 1, key);
}

void Heap_pop(Heap *h)
{
    if (h->size == 0) goto error;
    h->elems[0] = h->elems[h->size - 1];
    h->size--;
    Heapify(h, 0);
error:
    return;
}

Heap_elem Heap_top(const Heap *h) 
{
    return h->elems[0];
}
