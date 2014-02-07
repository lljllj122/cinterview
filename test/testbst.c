#include "../lib/minunit.h"
#include "../tree/bstree.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

BSTree *map = NULL;
static int traverse_called = 0;
static char *test1 = "test data 1";
static char *test2 = "test data 2";
static char *test3 = "test data 3";

static char *expect1 = "THE VALUE 1";
static char *expect2 = "THE VALUE 2";
static char *expect3 = "THE VALUE 3";

static int traverse_good_cb(BSTreeNode *node)
{
    debug("KEY: %s", (const char *)node->key);
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(BSTreeNode *node)
{
    debug("KEY: %s", (const char *)node->key);
    traverse_called++;

    if(traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

char *test_create()
{
    map = BSTree_create(NULL);
    mu_assert(map != NULL, "Failed to create map.");

    return NULL;
}

char *test_destroy()
{
    BSTree_destroy(map);

    return NULL;
}

char *test_get_set()
{
    int rc = BSTree_set(map, test1, expect1);
    mu_assert(rc == 0, "Failed to set &test1");
    char *result = BSTree_get(map, test1);
    mu_assert(strcmp(result, expect1) == 0, "Wrong value for test1.");

    rc = BSTree_set(map, test2, expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = BSTree_get(map, test2);
    mu_assert(strcmp(result, expect2) == 0, "Wrong value for test2.");

    rc = BSTree_set(map, test3, expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = BSTree_get(map, test3);
    mu_assert(strcmp(result, expect3) == 0, "Wrong value for test3.");

    return NULL;
}

char *test_traverse()
{
    int rc = BSTree_traverse(map, traverse_good_cb);
    mu_assert(rc == 0, "Failed to traverse.");
    mu_assert(traverse_called == 3, "Wrong count traverse.");

    traverse_called = 0;
    rc = BSTree_traverse(map, traverse_fail_cb);
    mu_assert(rc == 1, "Failed to traverse.");
    mu_assert(traverse_called == 2, "Wrong count traverse for fail.");

    return NULL;
}

char *test_delete()
{
    char *deleted = (char *)BSTree_delete(map, test1);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == expect1, "Should get test1");
    char *result = BSTree_get(map, test1);
    mu_assert(result == NULL, "Should delete.");

    deleted = (char *)BSTree_delete(map, &test1);
    mu_assert(deleted == NULL, "Should get NULL on delete");

    deleted = (char *)BSTree_delete(map, test2);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == expect2, "Should get test2");
    result = BSTree_get(map, test2);
    mu_assert(result == NULL, "Should delete.");

    deleted = (char *)BSTree_delete(map, test3);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == expect3, "Should get test3");
    result = BSTree_get(map, test3);
    mu_assert(result == NULL, "Should delete.");

    deleted = (char *)BSTree_delete(map, test3);
    mu_assert(deleted == NULL, "Should get NULL");
 
    return NULL;
}

char *test_fuzzing()
{
    BSTree *store = BSTree_create(NULL);
    int i = 0;
    int j = 0;
    /*char *numbers[100] = {NULL};*/
    int numbers[100] = {0};
    char *data[100] = {NULL};
    srand((unsigned int)time(NULL));

    for(i = 0; i < 100; i++) {
        int num = rand();
        char *buf = calloc(1, sizeof(char *));
        /*sprintf(buf, "%d", num);*/
        /*numbers[i] = buf;*/
        numbers[i] = num;
        sprintf(buf, "data %d", i);
        data[i] = buf;
        buf = NULL;
        /*debug("Val: %d", *numbers[i]);*/
        BSTree_set(store, &numbers[i], data[i]);
    }

    for(i = 0; i < 100; i++) {
        char *value = BSTree_delete(store, &numbers[i]);
        mu_assert(value == data[i], "Failed to delete the right number.");
        mu_assert(BSTree_delete(store, &numbers[i]) == NULL, "Should get nothing.");
    
        for(j = i+1; j < 99 - i; j++) {
            char *value = BSTree_get(store, &numbers[j]);
            mu_assert(value == data[j], "Failed to get the right number.");
        }
    
        value = NULL;
    }

    BSTree_destroy(store);

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
    mu_run_test(test_fuzzing);

    return NULL;
}

RUN_TESTS(all_tests);
