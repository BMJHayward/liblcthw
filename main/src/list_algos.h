#ifndef lcthy_List_algos_h
#define lcthw_List_algos_h

#include "list.h"

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *list, List_compare cmp);//cmp compares 2 values passed to it, returns the 2nd one if different

List *List_merge_sort(List *list, List_compare cmp);

#endif