#ifndef _array_darray_h
#define _array_darray_h
#include <stdlib.h>
#include <math.h>
#include "../lib/dbg.h"

typedef struct DArray {
    int num;
    int last;
    size_t element_size;
    void **data;
} DArray;

DArray *DArray_create(size_t element_size, size_t num);
void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);
int DArray_expand(DArray *array);
int DArray_contract(DArray *array);
int DArray_push(DArray *array, void *element);
void *DArray_pop(DArray *array);

#define SIZE 100

#define DArray_last(A) ((A)->data[(A)->last])
#define DArray_first(A) ((A)->data[0])
#define DArray_end(A) ((A)->last)
#define DArray_count(A) DArray_end(A)
#define DArray_num(A) ((A)->num)

static inline void DArray_set(DArray *array, int i, void *element)
{
    check(i < array->num, "setting: exceeded the max number of elements");
    if (i > array->last) {
        array->last = i;
    }
    array->data[i] = element;
error:
    return;
}

static inline void *DArray_get(DArray *array, int i)
{
    check(i < array->num, "getting: exceeded the max number of elements");
    return array->data[i];
error:
    return NULL; 
}

static inline void *DArray_remove(DArray *array, int i)
{
    void *element = array->data[i];
    array->data[i] = NULL;
    return element;
}

static inline void *DArray_new(DArray *array)
{
    check(array->element_size > 0, "new: array size is 0");
    return calloc(1, array->element_size);
error:
    return NULL;
}

#define DArray_free(E) free((E))

#endif
