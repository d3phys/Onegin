/**
 * \file
 * \brief  Onegin client
 * \author d3phys
 * \date   21.09.2021
 */
#ifndef ONEGIN_H_
#define ONEGIN_H_

#include <stddef.h>
#include "argv.h"
#include "sort.h"


const size_t MAX_OUT_FILES    = 32;
const size_t DESCRIPTION_SIZE = 128;

int sort();
int show_help();

struct config {
    int (*action)();
    const char *input_file;
    
    size_t n_output_files;
    const char *output_files[MAX_OUT_FILES];

    void (*sort_func)(void *, const size_t, const size_t, 
                       int (*)(const void *, const void *));

    int (*compare_func)(const void *, const void *);
};

int set_help_action(const char *args[], const size_t n_args);
int set_cfg_output(const char *args[], const size_t n_args);
int set_cfg_input (const char *args[], const size_t n_args);
int set_cfg_sort_func(const char *args[], const size_t n_args);
int set_cfg_comp_func(const char *args[], const size_t n_args);

const option ONEGIN_OPTIONS[] {
    {"from",    'f', set_cfg_input,     "sets input file"        },
    {"to",      't', set_cfg_output,    "sets output files"      },
    {"compare", 'c', set_cfg_comp_func, "sets the priority"      },
    {"help",    'h', set_help_action,   "prints this message"    },
    {"sort",    's', set_cfg_sort_func, "sets the sort algorithm"},
};

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

int compare_alpha_from_end(const void *item1, const void *item2);
int compare_alpha(const void *item1, const void *item2);

const priority PRIORITIES[] {
    {"forward",  compare_alpha},
    {"fromback", compare_alpha_from_end},
};


int construct_onegin_cfg(const int argc, const char *argv[]);

/**
 * \brief Main Onegin client procedure
 */
int onegin_client();

#endif // ONEGIN_H_
