#ifndef _bsearch_h
#define _bsearch_h
#include "../lib/dbg.h"
#include <stdlib.h>
#include <stddef.h>

typedef int (*cmp)(const void*, const void*);

int bsearch_int(const int a[], const int n, const int v);
void *bsearch_gen(const void *key, const void *ptr, size_t count, size_t size, cmp cmp);

typedef struct data {
    int id;
    char const *value;
} data;

static inline int cmp_int(const void *a, const void *b)
{
    // INT_MIN and INT_MAX have not been considered here
    int const *const ta = a;
    int const *const tb = b;
    return *ta - *tb;
}

//Comparison function from examples of C documents
static inline int cmp_struct(void const *a, void const *b)
{
    data const *const ta = a;
    data const *const tb = b;

    return ta->id - tb->id;
}

#endif
