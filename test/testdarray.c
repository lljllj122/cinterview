#include "../lib/minunit.h"
#include "../array/darray.h"
#include <assert.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
    array = DArray_create(sizeof(int), 100);
    mu_assert(array != NULL, "created: failed");
    mu_assert(array->data != NULL, "data is wrong");
    mu_assert(array->last == 0, "last is wrong");
    mu_assert(array->num == 100, "size is wrong");
    mu_assert(array->element_size == sizeof(int), "element size is wrong");

    return NULL;
}

char *test_new()
{
    val1 = DArray_new(array);
    mu_assert(val1 != NULL, "failed to make a new element");
    val2 = DArray_new(array);
    mu_assert(val2 != NULL, "failed to make a new element");

    return NULL;
}

char *test_set()
{
    DArray_set(array, 0, val1);
    DArray_set(array, 1, val2);

    return NULL;
}

char *test_get()
{
    mu_assert(DArray_get(array, 0) == val1, "wrong first value");
    mu_assert(DArray_get(array, 1) == val2, "wrong second value");

    return NULL;
}

char *test_remove()
{
    int *val1_check = DArray_remove(array, 0);
    mu_assert(val1_check != NULL, "remove: not null");
    mu_assert(*val1_check == *val1, "remove: first value wrong");
    mu_assert(DArray_get(array, 0) == NULL, "remove: not null value");
    DArray_free(val1_check);
    
    int *val2_check = DArray_remove(array, 1);
    mu_assert(val2_check != NULL, "remove: not null");
    mu_assert(*val2_check == *val1, "remove: second value wrong");
    mu_assert(DArray_get(array, 0) == NULL, "remove: not null value");
    DArray_free(val2_check);

    return NULL;
}

char *test_expand_contract()
{
    int oldnum = array->num;
    DArray_expand(array);
    mu_assert((unsigned int)array->num == oldnum * 2, "Expand: wrong size");

    DArray_contract(array);
    mu_assert((unsigned int)array->num == oldnum + 1, "Contract, wrong size");
    DArray_contract(array);
    mu_assert((unsigned int)array->num == (unsigned int)floor((double)(oldnum+1)/2.0) + 1, "Contract, wrong size");

    return NULL;
}

char *test_push_pop()
{
    int i = 0;
    for (i = 0; i < 1000; i++) {
        int *val = DArray_new(array);
        *val = i * 333;
        DArray_push(array, val);
    }

    mu_assert(array->num == 1632, "push: wrong size"); // 51 * 2 * 2 * 2 * 2 * 2

    for (i = 999; i >= 0; i--) {
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "pop: null");
        mu_assert(*val == i * 333, "pop: wrong value");
        DArray_free(val);
    }

    return NULL;
}

char *test_destory()
{
    DArray_destroy(array);
    return NULL;
}

char *all_tests() 
{
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_destory);

    return NULL;
}

RUN_TESTS(all_tests);
