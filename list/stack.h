#include <stdlib.h>
#include "lib/dbg.h"

typedef struct StackNode {
    struct StackNode *prev;
    struct StackNode *next;
    void *data;
} StackNode;

typedef struct Stack {
    int count;
    StackNode *top;
    StackNode *bottom;
} Stack;

#define Stack_peek(S) ((S)->top != NULL ? (S)->top->data : NULL)
#define Stack_count(S) ((S)->count)

static inline Stack *Stack_create()
{
    return calloc(1, sizeof(Stack));
}

static inline void Stack_destroy(Stack *stack)
{
    StackNode *v = NULL;

    for (v = stack->top; v != NULL; v = v->prev) {
        if (v->next) {
            free(v->next);
        }
    }

    free(stack->bottom);
    free(stack);
}

static inline void Stack_push(Stack *stack, void *data)
{
    StackNode *node = calloc(1, sizeof(StackNode));
    check_mem(node);

    node->data = data;

    if (stack->top == NULL) {
        stack->top = node;
        stack->bottom = node;
    } else {
        stack->top->next = node;
        node->prev = stack->top;
        stack->top = node;
    }

    stack->count++;
error:
    return;

}

static inline void *Stack_pop(Stack *stack)
{
    void *data = NULL;
    StackNode *node = stack->top;

    check(stack->top && stack->bottom, "empty stack");
    check(node, "null node");

    if (node->prev) {
        node->prev->next = NULL;
        stack->top = node->prev;
        check(stack->top != NULL, "pop error");
    } else {
        stack->bottom = NULL;
        stack->top = NULL;
    }

    stack->count--;
    data = node->data;
    free(node);

    return data;
error:
    return NULL;
}
