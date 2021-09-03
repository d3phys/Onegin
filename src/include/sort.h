#ifndef SORT_H_
#define SORT_H_

#include <cstddef>

void bubble_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*));

void insertion_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*));

void heap_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*));

#endif // SORT_H_
