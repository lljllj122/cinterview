#include "../lib/minunit.h"
#include "../list/dllist.h"
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "create: failed");

    return NULL;
}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "push: wrong value");
    List_push(list, test2);
    mu_assert(List_last(list) == test2, "push: wrong value");
    List_push(list, test3);
    mu_assert(List_last(list) == test3, "push: wrong value");
    mu_assert(List_count(list) == 3, "push: wrong count");

    char *val = List_pop(list);
    mu_assert(val == test3, "pop: wrong value");

    val = List_pop(list);
    mu_assert(val == test2, "pop: wrong value");

    val = List_pop(list);
    mu_assert(val == test1, "pop: wrong value");
    mu_assert(List_count(list) == 0, "pop: wrong count");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "unshift: wrong value");
    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "unshift: wrong value");
    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "unshift: wrong value");
    mu_assert(List_count(list) == 3, "unshift: wrong count");

    return NULL;
}

char *test_remove()
{
    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "remove: wrong value");
    mu_assert(List_count(list) == 2, "remove: wrong count");
    mu_assert(List_first(list) == test3, "remove: wrong value");
    mu_assert(List_last(list) == test1, "remove: wrong value");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "shift: wrong count");
    char *val = List_shift(list);
    mu_assert(val == test3, "shift: wrong value");
    val = List_shift(list);
    mu_assert(val == test1, "shift: wrong value");
    mu_assert(List_count(list) == 0, "shift: wrong count");
    return NULL;
}

char *test_destroy()
{
    List_clear(list);
    List_destroy(list);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
