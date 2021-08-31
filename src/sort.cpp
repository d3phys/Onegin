#include <cstddef>
#include <assert.h>
#include "include/sort.h"

int swap(void *item1, void *item2, int n_bytes) {
    if (item1 == item2)
        return 0;
    else if (item1 == nullptr || item2 == nullptr)
        return -1;
    else if (n_bytes < 0)
        return -2;

    char *elem1 = (char *)item1;
    char *elem2 = (char *)item2;
    char temp   = 0;

    while (n_bytes-- > 0){
        temp     = *elem1;
        *elem1++ = *elem2;
        *elem2++ = temp;
    }

    return 0;
}

void bubble_sort(void *items, const size_t n_items, const size_t item_size, 
                 int (*compare)(const void*, const void*)) {

    char *data = (char *)items;

    for (size_t i = 0; i < n_items; i++) {
        for (size_t j = 0; j < n_items - i - 1; j++) {
            if (compare(data + item_size * j, data + item_size * (j + 1)) > 0)
                swap(data + item_size * j, data + item_size * (j + 1), item_size);
        }
    }
}

