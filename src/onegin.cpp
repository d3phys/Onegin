#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "include/onegin.h"
#include "include/sort.h"
#include "include/argv.h"
#include "include/poem.h"

static config CONFIG = {0};

enum errors {
    ONEG_NO_INPUT_FILE  = -4,
    ONEG_NO_OUTPUT_FILE = -2,
    ONEG_SAVE_ERROR     = -3,
};

int construct_onegin_cfg(const int argc, const char *argv[]) {
    assert(argv);
    
    CONFIG.action       = sort;
    CONFIG.sort_func    = heap_sort;
    CONFIG.compare_func = compare_alpha;

int error = scan_args(argc, argv, ONEGIN_OPTIONS, 
                          sizeof(ONEGIN_OPTIONS) / sizeof(*ONEGIN_OPTIONS));

    if (error) {
        switch (error) {
            case ARGV_BAD_INPUT:
                fprintf(stderr, "Bad input\n");
                break;
            case ARGV_ACTION_FAIL:
                fprintf(stderr, "Action %s failed\n", argv_option());
                break;
            case ARGV_NO_KEYWORD:
                fprintf(stderr, "Keyword %s not found\n", argv_option());
                break;
            case ARGV_SYSTEM:
                fprintf(stderr, "System error\n");
                break;
            default:
                assert(nullptr);
        }

        return -1;
    }

    return 0;
}

int onegin_client() {
    int error = CONFIG.action();

    if (error) {
        switch (error) {
            case ONEG_NO_INPUT_FILE:
                fprintf(stderr, "No input file error\n");
                break;
            case ONEG_NO_OUTPUT_FILE:
                fprintf(stderr, "No output file error\n");
                break;
            case ONEG_SAVE_ERROR:
                fprintf(stderr, "Saving error\n");
                break;
            default:
                fprintf(stderr, "Onegin failed\n");
                break;
        }

        return -1;
    }

    return 0;
}

int sort() {
    if (CONFIG.input_file == nullptr)
        return ONEG_NO_INPUT_FILE;

    if (CONFIG.n_output_files == 0) 
        return ONEG_NO_OUTPUT_FILE;

    char *const buff = buffer(CONFIG.input_file);
    if (buff == nullptr)
        return -1;

    int error = 0;
    poem_t poem = {0};

    error = construct_poem(&poem, buff);
    if (error) {
        free(buff);
        return -1;
    }

    error = cross_out(&poem, rule_empty);
    if (error) {
        destruct_poem(&poem);
        free(buff);
        return -1;
    }

    CONFIG.sort_func(poem.lines, poem.n_lines, sizeof(line_t), CONFIG.compare_func);

    error = 0;
    for (size_t i = 0; i < CONFIG.n_output_files; i++) {
        error += save_poem(&poem, CONFIG.output_files[i]);
    }

    destruct_poem(&poem);
    free(buff);

    if (error) 
        return ONEG_SAVE_ERROR; 

    return 0;
}

int show_help() {
    size_t n_options = sizeof(ONEGIN_OPTIONS) / sizeof(*ONEGIN_OPTIONS);
    for (size_t i = 0; i < n_options; i++) {
        printf("-%c | -%-*s - %-*s\n", ONEGIN_OPTIONS[i].short_keword, 
                (int)KEYWORD_SIZE,     ONEGIN_OPTIONS[i].keyword,
                (int)DESCRIPTION_SIZE, ONEGIN_OPTIONS[i].description);
    }
    return 0;
}

int set_sort_action(const char *args[], const size_t n_args) {
    if (n_args != 1)
        return -1;

    CONFIG.action = sort;
    return 0;
}

int set_help_action(const char *args[], const size_t n_args) {
    if (n_args != 1)
        return -1;

    CONFIG.action = show_help;
    return 0;
}

int set_cfg_output(const char *args[], const size_t n_args) {
    if (n_args < 2 || n_args > MAX_OUT_FILES + 1)
        return -1;

    size_t n_out = 0;
    for (n_out = 0; n_out < n_args - 1; n_out++)
        CONFIG.output_files[n_out] = args[n_out + 1];

    CONFIG.n_output_files = n_out;

    return 0;
}

int set_cfg_input (const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    CONFIG.input_file = args[1];
    return 0;
}

int set_cfg_sort_func(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    const char *sort = args[1];

    size_t n_algs = sizeof(ALGORITHMS) / sizeof(*ALGORITHMS);
    for (int i = 0; i < n_algs; i++)
        if (strncmp(ALGORITHMS[i].name, sort, KEYWORD_SIZE) == 0) {
            CONFIG.sort_func= ALGORITHMS[i].sort_func;
            return 0;
        }

    return -1;
}

int set_cfg_comp_func(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    const char *comp = args[1];

    size_t n_priorities = sizeof(PRIORITIES) / sizeof(*PRIORITIES);
    for (int i = 0; i < n_priorities; i++)
        if (strncmp(PRIORITIES[i].name, comp, KEYWORD_SIZE) == 0) {
            CONFIG.compare_func = PRIORITIES[i].compare_func;
            return 0;
        }

    return -1;
}

int compare_alpha_from_end(const void *item1, const void *item2) {
    return cmp_alpha_punct_ignored_from_end(*(line_t*)item1, *(line_t*)item2);
}

int compare_alpha(const void *item1, const void *item2) {
    return cmp_alpha_punct_ignored(*(line_t*)item1, *(line_t*)item2);
}
