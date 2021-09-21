/**
 * \file
 * \brief  Onegin client
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef ONEGIN_H_
#define ONEGIN_H_

#include "compare.h"
#include "error_t.h"
#include "argv.h"
#include "sort.h"
#include <cstddef>

const size_t MAX_OUT_FILES    = 0x20;
const size_t DESCRIPTION_SIZE = 100;

int sort();
int format();

struct config {
    int (*action)();
    const char *input_file;
    
    size_t n_output_files;
    const char *output_files[MAX_OUT_FILES];

    void (*sort_func)(void *, const size_t, const size_t, 
                       int (*)(const void *, const void *));

    int (*compare_func)(const void *, const void *);
};
/*
int set_format_action(const char *args[], const size_t n_args);
int set_cfg_output(const char *args[], const size_t n_args);
int set_cfg_input (const char *args[], const size_t n_args);
int set_cfg_sort_func(const char *args[], const size_t n_args);
int set_cfg_comp_func(const char *args[], const size_t n_args);
int set_log_file(const char *args[], const size_t n_args);
int show_onegin_help(const char *args[], const size_t n_args);
const option ONEGIN_OPTIONS[] {
    {"from",    'f', set_cfg_input,     "sets input file"        },
    {"to",      't', set_cfg_output,    "sets output files"      },
    {"compare", 'c', set_cfg_comp_func, "sets the priority"      },
    {"help",    'h', show_onegin_help,  "prints this message"    },
    {"sort",    's', set_cfg_sort_func, "sets the sort algorithm"},
    {"log",     'l', set_log_file,      "sets the log file"      },
    {"format",  'b', set_format_action, "Format input text and outputs it" },
};
*/
struct sort_algorithm {
    const char *name;
    void (*sort_func)(void *, const size_t, const size_t, 
                       int (*)(const void *, const void *));
};

const sort_algorithm ALGORITHMS[] {
    {"heap",      heap_sort},
    {"bubble",    bubble_sort},
    {"insertion", insertion_sort},
};

struct priority {
    const char *name;
    int (*compare_func)(const void *, const void *);
};

const priority PRIORITIES[] {
    {"alpha",  compare_alpha},
    {"alphar", compare_alpha_rev},
};

int construct_onegin_cfg(const int argc, const char *argv[]);

/**
 * \brief Main Onegin client procedure
 */
int onegin_client();

#endif // ONEGIN_H_
