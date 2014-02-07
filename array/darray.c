#include "darray.h"

DArray *DArray_create(size_t element_size, size_t num)
{
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    array->num = num;
    array->data = calloc(num, sizeof(void *));
    check_mem(array->data);
    array->last = 0;
    array->element_size = element_size;
    return array;
error:
    if (array) free(array);
    return NULL;
}

void DArray_clear(DArray *array)
{
    int i = 0;
    if (array->element_size > 0) {
        for (i = 0; i < array->num; i++) {
            if (array->data[i] != NULL) {
                free(array->data[i]);
            }
        }
    }
}

void DArray_destroy(DArray *array)
{
    if (array) {
        if (array->data) free(array->data);
        free(array);
    }
}

static inline int DArray_resize(DArray *array, size_t newsize)
{
    array->num = newsize;
    check(array->num > 0, "newsize: size is less than 0");
    void *data = realloc(array->data, array->num * sizeof(void *));
    check_mem(data);
    array->data = data;
    return 0;
error:
    return -1;
}

int DArray_expand(DArray *array)
{
    size_t oldnum = array->num;
    int result = DArray_resize(array, array->num * 2);
    check(result == 0, "expand: failed");
    memset(array->data + oldnum, 0, oldnum + 1);
    return 0;
error:
    return -1;
}

int DArray_contract(DArray *array)
{
    int halfsize = (int)floor((double)array->num/2.0);
    int newsize = array->last < halfsize ? halfsize : array->last;
    return DArray_resize(array, newsize + 1);
}

int DArray_push(DArray *array, void *element)
{
    array->data[array->last] = element;
    array->last++;

    if (DArray_end(array) >= DArray_num(array)) {
        return DArray_expand(array);
    } else {
        return 0;
    }
}

void *DArray_pop(DArray *array)
{
    check(array->last-1 >= 0, "pop: empty");

    void *element = DArray_remove(array, array->last-1);
    array->last--;

    if (DArray_end(array) < (int)floor((double)array->num/2.0)) {
        DArray_contract(array);
    }
    return element;
error:
    return NULL;
}
