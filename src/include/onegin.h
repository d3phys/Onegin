/**
 * \file
 * \brief  Onegin client
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef ONEGIN_H_
#define ONEGIN_H_

#include "error_t.h"
#include "argv.h"
#include <cstddef>

const size_t MAX_OUT_FILES = 32;

struct config {
    const char *input_file;
    
    size_t n_output_files;
    const char *output_files[MAX_OUT_FILES];

    void (*sort_func)(void *, const size_t, const size_t, 
                       int (*)(const void *, const void *));

    int (*compare_func)(const void *, const void *);
};

int set_cfg_output(const char *args[], const size_t n_args);
int set_cfg_input (const char *args[], const size_t n_args);
int set_cfg_sort_func(const char *args[], const size_t n_args);
int set_cfg_comp_func(const char *args[], const size_t n_args);

int show_onegin_help(const char *args[], const size_t n_args);

const option ONEGIN_OPTIONS[] {
    {"h",       show_onegin_help},
    {"help",    show_onegin_help},
    {"i",       set_cfg_input},
    {"input",   set_cfg_input},
    {"o",       set_cfg_output},
    {"output",  set_cfg_output},
    {"s",       set_cfg_sort_func},
    {"sort",    set_cfg_sort_func},
    {"c",       set_cfg_comp_func},
    {"compare", set_cfg_comp_func},
};

int construct_onegin_cfg(const int argc, const char *argv[]);

/**
 * \brief Main Onegin client procedure
 */
int onegin_client();

#endif // ONEGIN_H_
