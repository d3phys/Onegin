#include "include/sort.h"
#include <assert.h>
#include <stdint.h>

#define SWAP(type, size, temp, chunk1, chunk2) \
        temp            = *(type *)chunk1;     \
        *(type *)chunk1 = *(type *)chunk2;     \
        *(type *)chunk2 = temp;                \
                                               \
        chunk1 = (type *)chunk1 + 1;           \
        chunk2 = (type *)chunk2 + 1;           \
        n_bytes -= size;

int swap(void *chunk1, void *chunk2, int n_bytes) {
    int64_t temp = 0;

    while (n_bytes >= 8) {
        SWAP(int64_t, 8, temp, chunk1, chunk2);
    }

    if (n_bytes >= 4) {
        SWAP(int32_t, 4, temp, chunk1, chunk2);
    }

    if (n_bytes >= 2) {
        SWAP(int16_t, 2, temp, chunk1, chunk2);
    }
    
    if (n_bytes >= 1) {
        SWAP(int8_t,  1, temp, chunk1, chunk2);
    }

    return 0;
}
#undef SWAP

int swap_s(void *item1, void *item2, int n_bytes) {
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
    assert(items);
    assert(item_size);
    assert(compare);

    char *data = (char *)items;

    for (size_t i = 0; i < n_items; i++) {
        for (size_t j = 0; j < n_items - i - 1; j++) {
            if (compare(data + item_size * j, data + item_size * (j + 1)) > 0)
                swap(data + item_size * j, data + item_size * (j + 1), item_size);
        }
    }
}

void insertion_sort(void *items, const size_t n_items, const size_t item_size, 
                    int (*compare)(const void*, const void*)) {
    assert(items);
    assert(item_size);
    assert(compare);

    char *data = (char *)items;
    
    size_t curr = 0;
    for (size_t i = 1; i < n_items; i++) {
        curr = i;
        while (compare(data + item_size * curr, data + item_size * (curr - 1)) < 0) {
            swap(      data + item_size * curr, data + item_size * (curr - 1), item_size);
            if (--curr == 0)
                break;
        }
    }
}

void heap_sort(void *items, const size_t n_items, const size_t item_size, 
                    int (*compare)(const void*, const void*)) {
    if (n_items < 2)
        return;

    char *data = (char *)items;
    
    size_t root   = 0;
    size_t branch = 0;
    size_t i      = (n_items / 2 - 1);

    do {
        for (root = i; 2 * root + 1 < n_items; root = branch) {
            branch = root * 2 + 1;
            if (branch < n_items - 1 && 
                compare(data + branch * item_size, data + (branch + 1) * item_size) < 0)
                branch++;
            if (compare(data + branch * item_size, data + root * item_size) > 0)
                swap(data + branch * item_size, data + root * item_size, item_size);
        }
    } while (i-- > 0);

    for (size_t n_swapped = n_items - 1; n_swapped > 0; n_swapped--) {
        swap(data, data + n_swapped * item_size, item_size);
        for (root = 0; 2 * root + 1 < n_swapped; root = branch) {
            branch = root * 2 + 1;
            if (branch < n_swapped - 1 && compare(data + branch * item_size, 
                                                  data + (branch + 1) * item_size) < 0)
                branch++;
            if (compare(data + branch * item_size, data + root * item_size) > 0)
                swap(data + branch * item_size, data + root * item_size, item_size);
        }
    }
}
