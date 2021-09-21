#ifndef _ARGV_H_
#define _ARGV_H_

#include <cstddef>
#include <stdio.h>

enum argv_error_t {
    ARGV_SYSTEM       = -300,
    ARGV_NO_KEYWORD   = -1,
    ARGV_BAD_INPUT    = -2,
    ARGV_ACTION_FAIL  = -3,
};

const size_t KEYWORD_SIZE  = 32;
const size_t OPTION_PREFIX = '-';

const char *argv_option();

struct option {
    const char *keyword;
    char short_keword;
    int (*action)(const char *args[], const size_t n_args);
    const char *description;
};

const option *find_option(const option *options, const size_t n_options, 
                          const char *keyword, const size_t keyword_size = KEYWORD_SIZE);

int scan_args(const int argc, const char *argv[], 
                      const option *options, const size_t n_options, 
                      const size_t prefix = OPTION_PREFIX, const size_t keyword_size = KEYWORD_SIZE);


#endif // _ARGV_H_
