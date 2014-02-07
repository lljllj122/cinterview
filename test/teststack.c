#include "../lib/minunit.h"
#include "../stack.h"
#include <assert.h>

#define NUMS 3
static Stack *stack = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};

char *test_create()
{
    stack = Stack_create();
    mu_assert(stack != NULL, "creat: failed");

    return NULL;
}

char *test_pop_push()
{
    int i;
    for (i = 0; i < NUMS; i++) {
        Stack_push(stack, tests[i]);
        mu_assert(Stack_peek(stack) == tests[i], "wrong value");
    }

    mu_assert(Stack_count(stack) == NUMS, "wrong count");

    StackNode *v = NULL;

    for (v = stack->top; v != NULL; v = v->prev) {
        debug("Val: %s", (char *)v->data);
    }

    for (i = NUMS -1; i >= 0; i--) {
        char *val = Stack_pop(stack);
        mu_assert(val == tests[i], "wrong value");
    }

    mu_assert(Stack_count(stack) == 0, "wrong count after poping");

    return NULL;
}

char *test_destroy()
{
    mu_assert(stack != NULL, "destroy: failed");
    Stack_destroy(stack);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_pop_push);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
