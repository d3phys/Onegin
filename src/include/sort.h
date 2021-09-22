/**
 * \file 
 * \brief  Sort alghorithms
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef SORT_H_
#define SORT_H_

#include <stddef.h>

/**
 * \brief Sorts an array using bubble sort alghorithm
 *
 * \param items     Array to sort
 * \param n_items   Items count
 * \param item_size Item size in bytes
 * \param compare   Comparator function
 */
void bubble_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*));

/**
 * \brief Sorts an array using insertion sort alghorithm
 *
 * \param items     Array to sort
 * \param n_items   Items count
 * \param item_size Item size in bytes
 * \param compare   Comparator function
 */
void insertion_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*));

/**
 * \brief Sorts an array using heap sort alghorithm
 *
 * \param items     Array to sort
 * \param n_items   Items count
 * \param item_size Item size in bytes
 * \param compare   Comparator function
 */
void heap_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*));

#endif // SORT_H_
