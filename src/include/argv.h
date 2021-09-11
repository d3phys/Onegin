#ifndef _ARGV_H_
#define _ARGV_H_

#include <cstddef>
#include <stdio.h>

#define ERROR_OUTPUT /* Define if you need an automatic error output */

extern FILE *LOG;

enum argv_error_t {
    ARGS_NUMBER_OVERFLOW = 1,
    INCORRECT_INPUT      = 2,
    INVALID_ARGS_TYPE    = 3,
    KEYWORD_NOT_FOUND    = 4,
};

const size_t KEYWORD_SIZE  = 32;
const size_t OPTION_PREFIX = '-';

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
