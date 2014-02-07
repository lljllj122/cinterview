#include "bsearch.h"

int bsearch_int(const int a[], const int n, const int v)
{
    int left = 0, right = n - 1, mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);

        if (a[mid] == v) {
            return mid; 
        } else if (a[mid] < v) {
            left = mid + 1; 
        } else {
            right = mid - 1;
        }
    }

    return -(left + 1);
}

void *bsearch_gen(const void *key, const void *ptr, size_t count, size_t size, cmp cmp)
{
    int left = 0, right = count - 1, mid, ret;

    /*log_info("%zu", size);*/
    
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        ret = cmp(key, ptr+mid*size);

        /*log_info("%d : %d, %d : %d", mid, *(int *)key, *(int *)(ptr + mid * size), ret);*/

        if (ret == 0) {
            return (void *)(ptr+mid * size);
        } else if (ret > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return NULL;
}
