#include "../lib/minunit.h"
#include "../dict/hashtable.h"
#include <assert.h>

Hashtable *table = NULL;
static int traverse_called = 0;
static char *test1 = "test data 1";
static char *test2 = "test data 2";
static char *test3 = "test data 3";
static char *expect1 = "THE VALUE 1";
static char *expect2 = "THE VALUE 2";
static char *expect3 = "THE VALUE 3";

static int traverse_good_cb(HashtableNode *node)
{
    debug("KEY: %s", (char *)node->key);
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(HashtableNode *node)
{
    debug("KEY: %s", (char *)node->key);
    traverse_called++;
    if (traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

char *test_create()
{
    table = Hashtable_create(NULL, NULL);
    mu_assert(table != NULL, "create: failed");

    return NULL;
}

char *test_get_set()
{
    int rc = Hashtable_set(table, test1, expect1);
    mu_assert(rc == 0, "set: failed, test1");
    char *result = Hashtable_get(table, test1);
    debug("%s", result);
    mu_assert(result == expect1, "wrong value for test1");

    rc = Hashtable_set(table, test2, expect2);
    mu_assert(rc == 0, "set: failed, test2");
    result = Hashtable_get(table, test2);
    debug("%s", result);
    mu_assert(result == expect2, "wrong value for test2");

    rc = Hashtable_set(table, test3, expect3);
    mu_assert(rc == 0, "set: failed, test3");
    result = Hashtable_get(table, test3);
    debug("%s", result);
    mu_assert(result == expect3, "wrong value for test3");

    return NULL;
}

char *test_traverse()
{
    int rc = Hashtable_traverse(table, traverse_good_cb);
    mu_assert(rc == 0, "traverse: failed");
    mu_assert(traverse_called == 3, "wrong count traverse");

    traverse_called = 0;
    rc = Hashtable_traverse(table, traverse_fail_cb);
    mu_assert(rc == 1, "traverse: failed");
    mu_assert(traverse_called == 2, "wrong count traverse for fail");

    return NULL;
}

char *test_delete()
{
    char *deleted = Hashtable_delete(table, test1);
    mu_assert(deleted != NULL, "delete: NULL");
    mu_assert(deleted == expect1, "delete: wrong value");
    char *result = Hashtable_get(table, test1);
    mu_assert(result == NULL, "delete: should be deleted");

    deleted = Hashtable_delete(table, test2);
    mu_assert(deleted != NULL, "delete: NULL");
    mu_assert(deleted == expect2, "delete: wrong value");
    result = Hashtable_get(table, test2);
    mu_assert(result == NULL, "delete: should be deleted");

    deleted = Hashtable_delete(table, test3);
    mu_assert(deleted != NULL, "delete: NULL");
    mu_assert(deleted == expect3, "delete: wrong value");
    result = Hashtable_get(table, test3);
    mu_assert(result == NULL, "delete: should be deleted");

    return NULL;
}

char *test_destroy()
{
    Hashtable_destroy(table);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
