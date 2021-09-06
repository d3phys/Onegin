#include "include/sort.h"
#include "include/onegin.h"
#include "include/test.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "include/compare.h"

#define TEST

int main(int argc, char *argv[]) {
    config cfg = {};
    onegin_cfg(&cfg, argc, argv);

    onegin_client(&cfg);
    
#ifdef TEST
    test_sorts();
#endif

    return 0;
}
