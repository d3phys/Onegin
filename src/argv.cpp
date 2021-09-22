#include <assert.h>
#include <string.h>
#include "include/argv.h"

static const char *CURRENT_OPTION = nullptr;

const char *argv_option() { 
    return CURRENT_OPTION; 
}

int scan_args(const int argc, const char *argv[], 
              const option *options, const size_t n_options, 
              const size_t prefix, const size_t keyword_size) {
    assert(options);
    assert(argv);

    size_t n_args = 0;
    size_t arg    = 0;

    const option *option = nullptr;
    size_t op = 0;
    for (op = 1; op < argc; op += n_args) {
        CURRENT_OPTION = argv[op];

        if (*argv[op] != prefix)
            return ARGV_BAD_INPUT;

        option = find_option(options, n_options, argv[op], keyword_size);
        if (option == nullptr)
            return ARGV_NO_KEYWORD;

        n_args = 1;
        for (arg = op + 1; arg < argc; n_args++)
            if (*argv[arg++] == prefix) 
                break;

        int error = option->action(argv + op, n_args);
        if (error)
            return ARGV_ACTION_FAIL;
    }

    return 0;
}

const option *find_option(const option *options, const size_t n_options, 
                          const char *keyword, const size_t keyword_size) {
    assert(options);
    assert(keyword);

    if (strlen(keyword) == 2) {
        for (size_t i = 0; i < n_options; i++)
            if (keyword[1] == options[i].short_keword)
                return (options + i);
    } else {
        for (size_t i = 0; i < n_options; i++) {
            if (strncmp(keyword + 1, options[i].keyword, keyword_size) == 0)
                return (options + i);
        }
    }

    return nullptr;
}


