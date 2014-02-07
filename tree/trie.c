#include "trie.h"

Trie_tree *Trie_create()
{
    Trie_tree *tree = (Trie_tree *)calloc(1, sizeof(Trie_tree));
    tree->root = &(tree->nodes[0]);
    memset(tree->nodes, 0, sizeof(tree->nodes));
    tree->size = 1;
    return tree;
}

void Trie_destroy(Trie_tree *tree)
{
    free(tree);
    tree = NULL;
}

void Trie_clear(Trie_tree *tree)
{
    memset(tree->nodes, 0, sizeof(tree->nodes));
    tree->size = 1;
}

bool Trie_insert(Trie_tree *tree, char *word)
{
    int i;
    Trie_node *p = tree->root;
    while (*word) {
        int curr = *word - '0';
        if (p->next[curr] == NULL) {
            p->next[curr] = &(tree->nodes[tree->size++]);
        }
        p = p->next[curr];
        if (p->is_tail) return false;

        word++;
    }

    p->is_tail = true;

    for (i = 0; i < CHAR_COUNT; i++) {
        if (p->next[i] != NULL) return false;
    }

    return true;
}
