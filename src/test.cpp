#include <stdio.h>
#include "include/compare.h"
//#include "include/test.h"
#include "include/sort.h"
#include <assert.h>

#define TEST_SORT(compare)                                                                \
    sort_func(test, sizeof(ans)/sizeof(*ans), sizeof(*ans), compare);                     \
    succeed = compare_sorted(test, ans, sizeof(ans)/sizeof(*ans), sizeof(*ans), compare); \
    if (succeed)                                                                          \
        n_succeed++;                                                                      \
    display_test(++n_tests, succeed);                                                     \

const char TEST_SUCCESS[] = "\u001b[32m✔\u001b[0m";
const char TEST_FAILURE[] = "\u001b[31m✘\u001b[0m";

void display_unit_init(const char *unit) {
    printf("------------------------------------\n"
           "Unit: %29s\n"
           "------------------------------------\n", unit);
}

void display_unit_result(const size_t n_tests, const size_t n_succeed, const size_t n_failed) {
    printf("------------------------------------\n"
           "Tests:%3ld \u001b[32mSuccess: %3ld \u001b[31mFailure: %3ld \u001b[0m\n"
           "------------------------------------\n", n_tests, n_succeed, n_failed);
}

void display_test(const size_t test_number, const bool succeed) {
    printf("Test#%2ld: %s\n", test_number, succeed ? TEST_SUCCESS : TEST_FAILURE);
}

int compare_sorted(void *items1, void *items2, const size_t n_items,
                   const size_t item_size, int (*compare)(const void*, const void*)) {
    char *arr1 = (char *)items1;
    char *arr2 = (char *)items2;

    for (size_t i = 0; i < n_items; i++) {
        if (compare(arr1 + item_size * i, arr2 + item_size * i) != 0)
            return 0;
    }
    return 1;
}

void test_sort(void sort_func(void *, const size_t, const size_t, 
               int (*)(const void*, const void*)), const char *sort_name) 
{
    assert(sort_func);

    size_t n_tests   = 0;
    size_t n_succeed = 0;
    bool   succeed   = false;

    display_unit_init(sort_name);

    /* Test */ {
    int test[] = {2, 4, 1, 5, 2, -9, 5, 7};
    int ans[]  = {-9, 1, 2, 2, 4, 5, 5, 7};
    TEST_SORT(compare_int);
    }

    {
        int test[] = {0};
        int ans[]  = {0};
        TEST_SORT(compare_int);
    }

    {
        int test[] = {0, 1, 2, 3, 4, 5};
        int ans[]  = {0, 1, 2, 3, 4, 5};
        TEST_SORT(compare_int);
    }

    /* Test */ {
    int test[] = {-23, 1, 333213124, 53, 3, 2};
    int ans[]  = {-23, 1, 2, 3, 53, 333213124};
    TEST_SORT(compare_int);
    }

    display_unit_result(n_tests, n_succeed, n_tests - n_succeed);
}

void test_sorts() {
    test_sort(bubble_sort, "bubble_sort");
    test_sort(insertion_sort, "insertion_sort");
    test_sort(heap_sort, "heap_sort");
}
