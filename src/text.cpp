#include <assert.h>
#include <cctype>
#include <cstdlib>
#include <string.h>
#include "include/text.h"

int not_endl(int ch) {
    return (ch != '\n' && ch != '\0');
}

size_t skip(const char **curr_pos, int (*valid)(int)) {
    assert(curr_pos);
    assert(valid);

    size_t n_skipped = 0;

    while(valid(**curr_pos) != 0) {
        n_skipped++;
        (*curr_pos)++;
    }

    return n_skipped;
}
// strtok strdup
size_t count_lines(const char *buffer) {
    assert(buffer);

    const char *curr_pos = buffer;
    size_t n_lines = 0;

    skip(&curr_pos, isspace);
    while (*curr_pos!= '\0') {
        skip(&curr_pos, not_endl);
        skip(&curr_pos, isspace);
        n_lines++;
    }

    return n_lines;
}

void extract_lines(const char *buffer, line *lines) {
    assert(buffer);
    assert(lines);

    skip(&buffer, isspace);
    while (*buffer != '\0') {
        lines->start  = buffer;
        lines->length = skip(&buffer, not_endl);
        lines++;

        skip(&buffer, isspace);
    }
}

size_t get_size(FILE *file) {
    assert(file);
//init pos fstat
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return file_size;
}

int construct_text(text_t *text, FILE *file) {
    assert(text);
    assert(file);

    size_t file_size = get_size(file); //ftell fstat stat

    text->buffer = (char *)calloc(file_size + 1, sizeof(char));
    if (text->buffer == nullptr)
        return BAD_ALLOC;

    fread(text->buffer, sizeof(char), file_size, file); //file_size = fread windows
    if (ferror(file) != 0)
        return FERROR;
    // realloc!!! 

    text->n_lines = count_lines(text->buffer);
    text->lines = (line *)calloc(text->n_lines, sizeof(line));
    if (text->lines == nullptr)
        return BAD_ALLOC;

    extract_lines(text->buffer, text->lines);

    return SUCCESS;
}

void destruct_text(text_t *text) {
    assert(text);

    free(text->lines);
    free(text->buffer);
}
