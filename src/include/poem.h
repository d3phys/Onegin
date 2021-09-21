/**
 * \file
 * \brief  Text analysis
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef POEM_H_
#define POEM_H_

#include <stdio.h>
#include "error_t.h"

/**
 * \brief Text line
 *
 * \details Line means a string without '\0' and '\n' symbol
 */
struct line {
    const char *start = nullptr; /**< Pointer to the line start */
    const char *end   = nullptr;
    size_t     length = 0;       /**< Line length without '\0'  */
};

/**
 * \brief Text
 *
 * \details Main poem object. Contains poem information.
 */
struct poem_t {
    line *lines    = nullptr; /**< Text lines                 */
    size_t n_lines = 0;       /**< Lines has been read        */
};

char *buffer(const char *const file);
int save_poem(const poem_t *const poem, const char *const file);
int cross_out(poem_t *const poem, int (*rule)(const line line));

int rule_empty(const line line);
/**
 * \brief Counts lines in a poem buffer
 *
 * \details Line ends with '\0' or '\\n'
 *
 * \param buffer Text buffer
 */
size_t count_lines(const char *const buffer);

/**
 * \brief Extracts lines from buffer to the lines array
 *
 * \param buffer Text buffer
 * \param lines  Lines array
 */
void extract_lines(const char *const buffer, line *lines);

/**
 * \brief Text object constructor
 *
 * \details This function skips all isspace symbols ('\\t' '\\n' '\\b' etc)
 *
 * \param poem      Text to create 
 * \param file_name File that contains lines
 */
int construct_poem(poem_t *const poem, const char *const buffer);

/**
 * \brief Text object destructor 
 */
void destruct_poem(poem_t *poem);

/**
 * \brief Counts file size in bytes
 */
off_t get_size(const char *const file);


int cmp_alpha(const line line1, const line line2);
int cmp_alpha_from_end(const line line1, const line line2);
int cmp_alpha_punct_ignored(const line line1, const line line2);
int cmp_alpha_punct_ignored_from_end(const line line1, const line line2);


#endif // POEM_H_
