#include "include/sort.h"
#include "include/onegin.h"
#include "include/test.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "include/compare.h"

//#define TEST

int main(const int argc, const char *argv[]) {
    if (construct_onegin_cfg(argc, argv) == 0)
        onegin_client();
    
#ifdef TEST
    test_sorts();
#endif

    return 0;
}
