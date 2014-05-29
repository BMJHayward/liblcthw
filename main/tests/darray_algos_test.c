#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)//simple a b comparison, strcmp() from stdlib.h
{
    return strcmp(*a, *b);
}

DArray *create_words()//creates 2d 5 long with string data in each place
{
    DArray *result = DArray_create(0, 5);
    char *words[] = {"asdfasdf", "werwar", "13245", "afdsafds", "yolocunt"};
    int i = 0;

    for(i = 0; i < 5; i++) {
        DArray_push(result, words[i]);
    }

    return result;

}

int is_sorted(DArray *array)//checks two adjacent elements in array, if in order, success
{
    int i = 0;

    for(i = 0; i < DArray_count(array) - 1; i++) {
        if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0) {
            return 0;
        }
    }

    return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)//takes a function, its name, creates an array, function runs on array, tests the sort result, then destroys array
{
    DArray *words = create_words();
    mu_assert(!is_sorted(words), "Words should start not sorted.");

    debug("--- Testing %s sorting algorithm", name);
    int rc = func(words, (DArray_compare)testcmp);
    mu_assert(rc == 0, "sort failed");
    mu_assert(is_sorted(words), "didn't sort it");

    DArray_destroy(words);

    return NULL;
}

char *test_qsort()//next 3 fns run each test
{
    return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
    return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
    return run_sort_test(DArray_mergesort, "mergesort");
}

char * all_tests()//runs all test like a boss
{
    mu_suite_start();

    mu_run_test(test_qsort);
    mu_run_test(test_heapsort);
    mu_run_test(test_mergesort);

    return NULL;
}

RUN_TESTS(all_tests);