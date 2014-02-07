#include "../lib/minunit.h"
#include "../tree/heap.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

Heap *heap = NULL;
const int size = 10;
int data[size] = {6, 2, 4, 3, 10, 20, 5, 7, 18, 9};

char *test_create()
{
    heap = Heap_create(NULL, 0, 100, NULL, MAX);
    mu_assert(heap != NULL, "Failed to create heap.");
    mu_assert(heap->size == 0, "Heap size is not correct");
    mu_assert(heap->cap == 100, "Heap cap is not correct");
    mu_assert(heap->type == MAX, "Heap type is not corrct");
    mu_assert(heap->elems != NULL, "Heap elems failed");

    return NULL;
}

char *test_build()
{
    heap = Heap_build(data, size, MAX);
    mu_assert(heap != NULL, "Failed to build heap from array");
    for (int i = 0; i < size; i++) {
        log_info("%d", heap->elems[i]);
    }

    return NULL;
}

char *test_empty()
{
    mu_assert(Heap_empty(heap) != 1, "Heap should not be empty");

    return NULL;
}

char *test_size()
{
    mu_assert(Heap_empty(heap) != 10, "Wrong size");

    return NULL;
}

char *test_change()
{
    Heap_change(heap, 5, 25);
    for (int i = 0; i < 10; i++) {
        log_info("%d", heap->elems[i]);
    }

    return NULL;
}

char *test_push()
{
    Heap_push(heap, 30);
    for (int i = 0; i < 11; i++) {
        log_info("%d", heap->elems[i]);
    }
    return NULL;
}

char *test_top()
{
    Heap_elem ret = Heap_top(heap);
    mu_assert(ret == 30, "Heap's values are not correct!");

    return NULL;
}

char *test_pop()
{
    Heap_pop(heap);
    for (int i = 0; i < 10; i++) {
        log_info("%d", heap->elems[i]);
    }

    return NULL;
}

char *test_destroy()
{
    Heap_destroy(heap);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);
    mu_run_test(test_build);
    mu_run_test(test_empty);
    mu_run_test(test_size);
    mu_run_test(test_change);
    mu_run_test(test_push);
    mu_run_test(test_top);
    mu_run_test(test_pop);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
