#include "include/sort.h"

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

int swap(void *item1, void *item2, int n_bytes) {
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

void insertion_sort(void *items, const size_t n_items, const size_t item_size, 
                    int (*compare)(const void*, const void*)) {

    char *data = (char *)items;
    
    size_t curr = 0;
    for (size_t i = 1; i < n_items; i++) {
        curr = i;
        while (compare(data + item_size * curr, data + item_size * (curr - 1)) < 0) {
            swap(data + item_size * curr, data + item_size * (curr - 1), item_size);
            if (--curr == 0)
                break;
        }
    }
}

void heap_sort(void *items, const size_t n_items, const size_t item_size, 
                    int (*compare)(const void*, const void*)) {

    char *data = (char *)items;
    
    size_t rt = 0;
    size_t br = 0;
    size_t i  = (n_items / 2 - 1) * item_size;

    do {
        for (rt = i; 2 * rt + 1 < n_items; rt = br) {
            br = rt * 2 + 1;
            if (br < n_items - 1 && 
                compare(data + br * item_size, data + (br + 1) * item_size) < 0)
                br++;
            if (compare(data + br * item_size, data + rt * item_size) > 0)
                swap(data + br * item_size, data + rt * item_size, item_size);
        }
    } while (i-- > 0);

    for (size_t n_swp = n_items - 1; n_swp > 0; n_swp--) {
        swap(data, data + n_swp * item_size, item_size);
        for (rt = 0; 2 * rt + 1 < n_swp; rt = br) {
            br = rt * 2 + 1;
            if (br < n_swp - 1 && 
                compare(data + br * item_size, data + (br + 1) * item_size) < 0)
                br++;
            if (compare(data + br * item_size, data + rt * item_size) > 0)
                swap(data + br * item_size, data + rt * item_size, item_size);
        }
    }
}
