//header for DArray_algos.c, declares DArray_compare and sort functions
#ifndef darray_algos_h
#define darray_algos_h

#include "darray.h"

typedef int (*DArray_compare)(const void *a, const void *b);

int DArray_qsort(DArray *array, DArray_compare cmp);

int DAarray_heapsort(DArray *array, DArray_compare cmp);

int DArray_mergesort(DArray *array, DArray_compare cmp);

#endif