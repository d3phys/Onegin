#ifndef TEXT_H_
#define TEXT_H_

#include <stdio.h>

struct line {
    const char *start = nullptr;
    size_t     length = 0;
};

struct text_t {
    FILE *file     = nullptr;
    line *lines    = nullptr;
    char *buffer   = nullptr;
    size_t n_lines = 0;
};

enum error_t {
    SUCCESS = 0,
    FOPEN   = 1,
    FCLOSE  = 2,
    ALLOC   = 3,
};

size_t skip(const char **curr_pos, int (*valid)(int));
int not_endl(int ch);

size_t count_lines(const char *buffer);
void   extract_lines(const char *buffer, line *lines);

error_t construct(text_t *text, const char *file_name);
void destruct(text_t *text);

size_t get_size(FILE *file);


#endif // TEXT_H_
