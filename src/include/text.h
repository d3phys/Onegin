/**
 * \file
 * \brief  Text analysis
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef TEXT_H_
#define TEXT_H_

#include <stdio.h>
#include "error_t.h"

/**
 * \brief Text line
 *
 * \details Line means a string without '\0' and '\n' symbol
 */
struct line {
    const char *start = nullptr; /**< Pointer to the line start */
    size_t     length = 0;       /**< Line length without '\0'  */
};

/**
 * \brief Text
 *
 * \details Main text object. Contains text information.
 */
struct text_t {
    FILE *file     = nullptr; /**< File to read from          */
    line *lines    = nullptr; /**< Text lines                 */
    char *buffer   = nullptr; /**< Buffer that contains lines */
    size_t n_lines = 0;       /**< Lines has been read        */
};


/**
 * \brief Skips valid characters.
 *
 * \details Moves text pointer to a new position. 
 *  Valid function should return non-zero value if character is not valid, and 0 otherwise.
 *
 * \code
 *
 *  // Valid function example
 *  int not_endl(int ch) {
 *      return (ch != '\n' && ch != '\0');
 *  }
 *
 * \endcode
 *
 * \param curr_pos Current text pointer
 * \param valid    Function that indicates the correctness of a character.
 */
size_t skip(const char **curr_pos, int (*valid)(int));
int not_endl(int ch);

/**
 * \brief Counts lines in a text buffer
 *
 * \details Line ends with '\0' or '\\n'
 *
 * \param buffer Text buffer
 */
size_t count_lines(const char *buffer);

/**
 * \brief Extracts lines from buffer to the lines array.
 *
 * \param buffer Text buffer
 * \param lines  Lines array
 */
void   extract_lines(const char *buffer, line *lines);

/**
 * \brief Text object constructor
 *
 * \details This function skips all isspace symbols ('\\t' '\\n' '\\b' etc)
 *
 * \param text      Text to create 
 * \param file_name File that contains lines
 */
error_t construct(text_t *text, const char *file_name);

/**
 * \brief Text object destructor 
 */
void destruct(text_t *text);

/**
 * \brief Counts file size in bytes
 */
size_t get_size(FILE *file);


#endif // TEXT_H_
