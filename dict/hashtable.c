#include "hashtable.h"
#include "../lib/dbg.h"
#include <string.h>

static int default_compare(void *a, void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

static uint32_t default_hash(void *a)
{
    size_t len = strlen((const char *)a);
    char *key = (char *)a;
    uint32_t hash, i;

    for (hash = i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

Hashtable *Hashtable_create(Hashtable_compare compare, Hashtable_hash hash)
{
    Hashtable *table = calloc(1, sizeof(Hashtable));
    check_mem(table);

    table->compare = compare == NULL ? default_compare : compare;
    table->hash = hash == NULL ? default_hash : hash;
    table->buckets = DArray_create(sizeof(DArray *), BUCKETS);
    table->buckets->last = table->buckets->num; 
    check_mem(table->buckets);

    return table;
error:
    if (table) {
        Hashtable_destroy(table);
    }
    return NULL;
}

void Hashtable_destroy(Hashtable *table)
{
    int i, j;

    if (table) {
        if (table->buckets) {
            for (i = 0; i < DArray_count(table->buckets); i++) {
                DArray *bucket = DArray_get(table->buckets, i);
                if (bucket) {
                    for (j = 0; j < DArray_count(bucket); j++) {
                        free(DArray_get(bucket, j));
                    }
                    DArray_destroy(bucket);
                }
            }
            DArray_destroy(table->buckets);
        }
        free(table);
    }
}

static inline HashtableNode *Hashtable_node_create(uint32_t hash, void *key, void *value)
{
    HashtableNode *node = calloc(1, sizeof(HashtableNode));
    check_mem(node);

    node->key = key;
    node->value = value;
    node->hash = hash;

    return node;
error:
    return NULL;
}

static inline DArray *Hashtable_find_bucket(Hashtable *table, void *key, int create, uint32_t *hash_out)
{
    uint32_t hash = table->hash(key);
    int bucket_num = hash % BUCKETS;
    check(bucket_num >= 0, "find invalid bucket");
    *hash_out = hash;

    DArray *bucket = DArray_get(table->buckets, bucket_num);

    if (!bucket && create) {
        bucket = DArray_create(sizeof(void *), BUCKETS);
        check_mem(bucket);
        DArray_set(table->buckets, bucket_num, bucket);
    }

    return bucket;

error:
    return NULL;
}

int Hashtable_set(Hashtable *table, void *key, void *value)
{
    uint32_t hash = 0;
    DArray *bucket = Hashtable_find_bucket(table, key, 1, &hash);
    check(bucket, "set error");

    HashtableNode *node = Hashtable_node_create(hash, key, value);
    check_mem(node);

    DArray_push(bucket, node);

    return 0;
error:
    return -1;
}

static inline int Hashtable_get_node(Hashtable *table, uint32_t hash, DArray *bucket, void *key)
{
    int i;

    for (i = 0; i < DArray_end(bucket); i++) {
        debug("Try: %d, %d", i, DArray_end(bucket));
        HashtableNode *node = DArray_get(bucket, i);
        if (node->hash == hash && table->compare(node->key, key) == 0) {
            return i;
        }
    }

    return -1;
}

void *Hashtable_get(Hashtable *table, void *key)
{
    uint32_t hash = 0;
    DArray *bucket = Hashtable_find_bucket(table, key, 0, &hash);
    if (!bucket) return NULL;

    int i = Hashtable_get_node(table, hash, bucket, key);
    if (i == -1) return NULL;

    HashtableNode *node = DArray_get(bucket, i);
    check(node != NULL, "Get: failed");

    return node->value;
error:
    return NULL;
}

void *Hashtable_delete(Hashtable *table, void *key)
{
    uint32_t hash = 0;
    DArray *bucket = Hashtable_find_bucket(table, key, 0, &hash);
    if (!bucket) return NULL;

    int i = Hashtable_get_node(table, hash, bucket, key);
    if (i == -1) return NULL;

    HashtableNode *node = DArray_get(bucket, i);
    void *value = node->value;
    free(node);

    HashtableNode *ending = DArray_pop(bucket);

    if (ending != node) {
        DArray_set(bucket, i, ending);
    }

    return value; 
}

int Hashtable_traverse(Hashtable *table, Hashtable_traverse_cb traverse_cb)
{
    int i, j;
    int rc = 0;

    for (i = 0; i < DArray_count(table->buckets); i++) {
        DArray *bucket = DArray_get(table->buckets, i);
        if (bucket) {
            for (j = 0; j < DArray_count(bucket); j++) {
                HashtableNode *node = DArray_get(bucket, j);
                rc = traverse_cb(node);
                if (rc != 0) return rc;
            }
        }
    }
    return 0;
}
