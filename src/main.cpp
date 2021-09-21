#include "include/sort.h"
#include "include/onegin.h"
//#include "include/test.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "include/compare.h"
#include <stdint.h>
#include "include/argv.h"
#include "include/debug.h"
#include <wctype.h>

//#define TEST

void print() {
   poem_t poem = {0};
   $V("%d", ispunct(','));
   char *buff = buffer("in");
   $V("%ld", (size_t)buff);
   construct_poem(&poem, buff);
   $V("%ld", poem.n_lines);
   int err = cross_out(&poem, rule_empty);
   $V("%ld", poem.n_lines);
   heap_sort(poem.lines, poem.n_lines, sizeof(line), compare_alpha_rev);
   save_poem(&poem, "in");
   destruct_poem(&poem);
   free(buff);
}

int main(const int argc, const char *argv[]) {
//    if (construct_onegin_cfg(argc, argv) == 0)
//        onegin_client();
 
   printf("%ld\n", get_size("ong.txt"));
   char *buff = buffer("ong.txt");
   //printf("%s", buff);
   free(buff);
   print();


   printf("%ld\n", get_size("ong.txt"));

#ifdef TEST
    test_sorts();
#endif

    return 0;
}
