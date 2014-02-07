#include <stddef.h>
#include <stdio.h>

typedef int elem;

typedef struct tbt_node {
    int ltag;
    int rtag;
    struct tbt_node *left;
    struct tbt_node *right;
    elem elem;
} tbt_node;

static void in_thread(tbt_node *p, tbt_node **pre);
static tbt_node *first(tbt_node *p);
static tbt_node *last(tbt_node *p);
static tbt_node *next(const tbt_node *p);
static tbt_node *pre(const tbt_node *p);

void create_in_thread(tbt_node *root)
{
    tbt_node *pre = NULL;
    if (root != NULL) {
        in_thread(root, &pre);
        pre->right = NULL;
        pre->rtag = 1;
    }
}

void in_order(tbt_node *root, int(*visit)(tbt_node*))
{
    tbt_node *p;
    for (p = first(root); p != NULL; p = next(p)) {
        visit(p);
    }
}

static void in_thread(tbt_node *p, tbt_node **pre)
{
    if (p != NULL) {
        in_thread(p->left, pre);
        if (p->left == NULL) {
            p->left = *pre;
            p->ltag = 1;
        }

        if ((*pre) != NULL && (*pre)->right == NULL) {
            (*pre)->right = p;
            (*pre)->rtag = 1;
        }
        *pre = p;
        in_thread(p->right, pre);
    }
}

static tbt_node *first(tbt_node *p) 
{
    if (p == NULL) return NULL;

    while (p->ltag == 0) {
        p = p->left;
    }

    return p;
}

static tbt_node *next(const tbt_node *p) 
{
    if (p->rtag == 0) {
        return first(p->right);
    } else {
        return p->right;
    }
}

static tbt_node *last(tbt_node *p)
{
    if (p == NULL) return NULL;

    while (p->rtag == 0) {
        p = p->right;
    }

    return p;
}

static tbt_node *prev(const tbt_node *p)
{
    if (p->ltag == 0) {
        return last(p->left);    
    } else {
        return p->left;
    }
}
