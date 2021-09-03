#include "include/compare.h"
#include <string.h>

int compare_int(const void *item1, const void *item2) {
    int i1 = *(int *)item1;
    int i2 = *(int *)item2;

    return (i1 > i2) - (i2 > i1);
}

int compare_alphabet(const void *item1, const void *item2) {
    const char *str1 = ((line *)item1)->start;
    const char *str2 = ((line *)item2)->start;

    while (*str1 == *str2) {
        str1++;
        str2++;
    }

    return (*str1 > *str2) - (*str2 > *str1);
}

int compare_back_alphabet(const void *item1, const void *item2) {
    line *ln1 = (line *)item1;
    line *ln2 = (line *)item2;

    const char *str1 = ln1->start;
    const char *str2 = ln2->start;

    str1 += ln1->length - 1;
    str2 += ln2->length - 1;

    while (*str1 == *str2) {
        str1--;
        str2--;
    }

    return (*str1 > *str2) - (*str2 > *str1);
}

