#ifndef _list_dllist_h
#define _list_dllist_h

#include <stdlib.h>

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_push(List *list, void *value);
void *List_pop(List *list);
void *List_shift(List *list);
void List_unshift(List *list, void *value);
void *List_remove(List *list, ListNode *node);

#define List_count(L) ((L)->count)
#define List_first(L) ((L)->first != NULL ? (L)->first->value : NULL)
#define List_last(L) ((L)->last != NULL ? (L)->last->value : NULL)

/*
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *v = NULL;\
    for(v = _node = L->S; _node != NULL; V = _node = _node->M)
*/

#endif
