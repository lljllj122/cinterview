#ifndef _dict_hashtable_h
#define _dict_hashtable_h

#include <stdint.h>
#include "../array/darray.h"

#define BUCKETS 100

typedef int (*Hashtable_compare)(void *a, void *b);
typedef uint32_t (*Hashtable_hash)(void *key);

typedef struct Hashtable {
    DArray *buckets;
    Hashtable_compare compare;
    Hashtable_hash hash;
} Hashtable;

typedef struct HashtableNode {
    void *key;
    void *value;
    uint32_t hash;
} HashtableNode;

typedef int (*Hashtable_traverse_cb)(HashtableNode *node);

Hashtable *Hashtable_create(Hashtable_compare, Hashtable_hash);
void Hashtable_destroy(Hashtable *table);
int Hashtable_set(Hashtable *table, void *key, void *value);
void *Hashtable_get(Hashtable *table, void *key);
int Hashtable_traverse(Hashtable *table, Hashtable_traverse_cb traverse_cb);
void *Hashtable_delete(Hashtable *table, void *key);

#endif
