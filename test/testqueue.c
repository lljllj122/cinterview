#include "../lib/minunit.h"
#include "../queue.h"
#include <assert.h>

#define NUMS 3
static Queue *queue = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};

char *test_create()
{
    queue = Queue_create();
    mu_assert(queue != NULL, "create: failed");
    return NULL;
}

char *test_enqueue_dequeue()
{
    int i;
    for (i = 0; i < NUMS; i++) {
        Queue_enqueue(queue, tests[i]);
        mu_assert(Queue_front(queue) == tests[0], "wrong value");
    }
    mu_assert(Queue_count(queue) == NUMS, "wrong count");

    QueueNode *v = NULL;
    for (v = queue->front; v != NULL; v = v->next) {
        debug("val: %s", (char *)v->data);
    }

    for (i = 0; i < NUMS; i++) {
        char *val = Queue_dequeue(queue);
        mu_assert(val == tests[i], "dequeue: wrong value");
    }

    mu_assert(Queue_count(queue) == 0, "wrong count after dequeue");
    
    return NULL;
}

char *test_destroy() 
{
    mu_assert(queue != NULL, "failed destroy");
    Queue_destroy(queue);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_enqueue_dequeue);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests)
