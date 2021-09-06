/**
 * \file
 * \brief  Onegin client
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef ONEGIN_H_
#define ONEGIN_H_

#include "error_t.h"
#include "config.h"
#include <cstddef>

struct config {
    const char *input_file;
    const char *output_file;

    void (*sort_func)(void *, const size_t, const size_t, 
                       int (*)(const void*, const void*));

    int (*compare_func)(const void*, const void*);
};

error_t onegin_cfg(config *cfg, int argc, char *argv[]);

/**
 * \brief Main Onegin client procedure
 */
error_t onegin_client(const config *cfg);

#endif // ONEGIN_H_
