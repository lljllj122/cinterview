#ifndef _trie_h
#define _trie_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __cplusplus
typedef char bool;
#define false 0
#define true 1
#endif

#define MAXN 10000
#define CHAR_COUNT 10
#define MAX_CODE_LEN 10
#define MAX_NODE_COUNT (MAXN * MAX_CODE_LEN + 1)

typedef struct Trie_node {
    struct Trie_node *next[CHAR_COUNT];
    bool is_tail;
} Trie_node;

typedef struct Trie_tree {
    Trie_node *root;
    int size;
    Trie_node nodes[MAX_NODE_COUNT];
} Trie_tree;

Trie_tree *Trie_create();
void Trie_destroy(Trie_tree *tree);
void Trie_clear(Trie_tree *tree);
bool Trie_insert(Trie_tree *tree, char *word);

#endif
