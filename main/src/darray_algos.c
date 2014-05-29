#include "darray_algos.h"
#include <stdlib.h>
//see freebsd.org or man pages for sorting documentation. Missing from wikipedia and cplusplus sites
int DArray_qsort(DArray *array, DArray_compare cmp)//see ex34/darray.* for details
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);//qsort takes elements from (DA*count(array)) in array->contents, each element is sizeof, cmp and reorders the whole array. Does not return a value, only re-orders the array.
    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);//same inputs as qsort, but heapsort implementation
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);//same inputs as qsort, but mergesort implementation
}