#include "../lib/minunit.h"
#include "../search/bsearch.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>


char *test_search_int()
{
    const int a[10] = {3, 10, 45, 78, 123, 765, 1032, 6503, 8000, 9999};
    int ret = bsearch_int(a, 10, 123);
    mu_assert(ret == 4, "Failed to search 123");
    ret = bsearch_int(a, 10, 9999);
    mu_assert(ret == 9, "Failed to search 9999");
    ret = bsearch_int(a, 10, 100);
    mu_assert(ret < 0, "That is not true!");

    return NULL;
}

char *test_search_gen()
{
    const int a[10] = {3, 10, 45, 78, 123, 765, 1032, 6503, 8000, 9999};
    int key = 123;
    int *res = (int *)bsearch_gen(&key, a, 10, sizeof(int), cmp_int);
    mu_assert(*res == 123, "Failed to search 123");
    key = 9999;
    res = (int *)bsearch_gen(&key, a, 10, sizeof(int), cmp_int);
    mu_assert(*res == 9999, "Failed to search 9999");
    key = 100;
    res = (int *)bsearch_gen(&key, a, 10, sizeof(int), cmp_int);
    mu_assert(res == NULL, "That is not happening!");
    return NULL;
}

char *test_search_gen2()
{
    /*data key = { .id = 3, .value = "Hello" };*/
    data key = { .id = 3 };
    data dat[] = {{1, "Foo"}, {2, "Bar"}, {3, "Hello"}, {4, "World"},};
    data const *res = bsearch_gen(&key, dat, sizeof(dat)/sizeof(dat[0]), sizeof(dat[0]), cmp_struct);
    mu_assert(res->id == 3 && strcmp(res->value, "Hello") == 0, "Failed to search id 3");
    data key2 = { .id = 5 };
    res = bsearch_gen(&key2, dat, sizeof(dat)/sizeof(dat[0]), sizeof(dat[0]), cmp_struct);
    mu_assert(res == NULL, "Hell No!");
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_search_int);
    /*mu_run_test(test_search_gen);*/
    mu_run_test(test_search_gen2);

    return NULL;
}

RUN_TESTS(all_tests);
