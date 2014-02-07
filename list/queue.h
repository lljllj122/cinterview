#include <stdlib.h>
#include "lib/dbg.h"

typedef struct QueueNode {
    struct QueueNode *prev;
    struct QueueNode *next;
    void *data;
} QueueNode;

typedef struct Queue {
    int count;
    QueueNode *front;
    QueueNode *back;
} Queue;


#define Queue_front(Q) ((Q)->front != NULL ? (Q)->front->data : NULL)
#define Queue_count(Q) ((Q)->count)

static inline Queue *Queue_create()
{
    return calloc(1, sizeof(Queue));
}

static inline void Queue_destroy(Queue *queue)
{
    QueueNode *v = NULL;

    for (v = queue->back; v != NULL; v = v->prev) {
        if (v->next) {
            free(v->next);
        }
    }

    free(queue->front);
    free(queue);
}

static inline void Queue_enqueue(Queue *queue, void *data)
{
    QueueNode *node = calloc(1, sizeof(QueueNode));
    check_mem(node);
    node->data = data;

    if (queue->front == NULL) {
        queue->front = node;
        queue->back = node;
    } else {
        queue->back->next = node;
        node->prev = queue->back;
        queue->back = node;
    }

    queue->count++;

error:
    return;
}

static inline void *Queue_dequeue(Queue *queue)
{
    void *data = NULL;
    QueueNode *node = queue->front;

    check(queue->front && queue->back, "dequeue: empty");
    check(node != NULL, "dequeue: NULL");
    
    if (node->next) {
        node->next->prev = NULL;
        queue->front = node->next;
        check(queue->front != NULL, "dequeue: error");
    } else {
        queue->front = NULL;
        queue->back = NULL;
    }

    data = node->data;
    queue->count--;
    free(node);

    return data;
error:
    return NULL;
}
