#include "include/argv.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define SHOW_ERROR(error, option) printf("\u001b[31m%s: %s\u001b[0m\n", error, option);

int scan_args(const int argc, const char *argv[], 
              const option *options, const size_t n_options, 
              const size_t prefix, const size_t keyword_size) {
    assert(options);
    assert(argv);

    size_t n_args = 0;
    size_t arg    = 0;

    size_t action_error = 0;

    const option *option = nullptr;
    size_t op = 0;
    for (op = 1; op < argc; op += n_args) {
        if (*argv[op] != prefix) {
#ifdef ERROR_OUTPUT
            SHOW_ERROR("Incorrect input", argv[op]);
#endif
            return INCORRECT_INPUT;
        }

        option = find_option(options, n_options, argv[op], keyword_size);
        if (option == nullptr) {
#ifdef ERROR_OUTPUT
            SHOW_ERROR("Option not found", argv[op]);
#endif
            return KEYWORD_NOT_FOUND;
        }

        n_args = 1;
        for (arg = op + 1; arg < argc; n_args++)
            if (*argv[arg++] == prefix) 
                break;
action_error = option->action(argv + op, n_args);
        if (action_error != 0) {
#ifdef ERROR_OUTPUT
            SHOW_ERROR("Option action error", argv[op]);
#endif
            return action_error;
        }
    }

    return 0;
}

#undef SHOW_ERROR

const option *find_option(const option *options, const size_t n_options, 
                          const char *keyword, const size_t keyword_size) {
    assert(options);
    assert(keyword);

    for (size_t i = 0; i < n_options; i++) {
        if (strncmp(keyword + 1, options[i].keyword, keyword_size) == 0)
            return (options + i);
    }

    return nullptr;
}
