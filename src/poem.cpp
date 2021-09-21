#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <bits/types/FILE.h>
#include <cctype>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "include/debug.h"
#include "include/poem.h"

size_t count_lines(const char *const buffer) {
    assert(buffer);

    const char *pos = buffer;
    size_t n_lines = 0;
    while (*pos != '\0')
        if (*pos++ == '\n')
            n_lines++;

    return n_lines;
}

const char *linetok(const char *const buffer) {
    static const char *token = nullptr;

    if (buffer)
        token = buffer;

    const char *const start = token;

    if (token) {
        while(*token != '\n') {
            if (*token == '\0') {
                token = nullptr;
                return start;
            }

            token++;
        }

        token++;
    }

    return start;
}

void extract_lines(const char *const buffer, line *lines) {
    assert(buffer);
    assert(lines);

    int carriage_return = 0;
    const char *ch = buffer;
    while (*ch != '\n' && *ch != '\0')
        if (*ch++ == '\r') {
            carriage_return = 1;
            break;
        }

    const char *token = linetok(buffer);
    lines->start = token;

    token = linetok(nullptr);
    while (token) {
        lines++;
        lines->start = token;
        (lines - 1)->length = lines->start - (lines - 1)->start - 1 - carriage_return;
        (lines - 1)->end    = (lines - 1)->start + (lines - 1)->length - 1;

        token = linetok(nullptr);
    }

    lines->length = strlen(lines->start);
    lines->end    = lines->start + lines->length - 1;
}

int cross_out(poem_t *const poem, int (*rule)(const line line)) {
    assert(poem);
    assert(rule);

    line* write = poem->lines;
    line* read  = poem->lines;
    line* end   = poem->lines + poem->n_lines;

    while (read != end) {
        if (rule(*read) == 0) {
            *write++ = *read;
        }
        read++;
    }

    poem->n_lines = write - poem->lines;
    poem->lines = (line *)realloc(poem->lines, sizeof(line) * (write - poem->lines));

    if (poem->lines == nullptr)
        return -1;

    return 0;
}

int rule_empty(const line line) {
    for (size_t i = 0; i < line.length; i++)
        if (isspace(line.start[i]) == 0)
            return 0;

    return 1;
}

off_t get_size(const char *const file) {
    assert(file);

    struct stat buff;
    int error = stat(file, &buff);
    if (error)
        return -1;

    return buff.st_size;
}

char *buffer(const char *const file) {
    assert(file);

    off_t file_size = get_size(file);
    if (file_size < 0)
        return nullptr;

    int fd = open(file, O_RDONLY); 
    if (fd < 0)
        return nullptr;

    char *buffer = (char *)calloc(file_size + 1, sizeof(char));
    if (buffer == nullptr) {
        close(fd);
        return nullptr;
    }

    size_t n_read = read(fd, buffer, file_size + 1);
    if (n_read < 0) {
        free(buffer);
        close(fd);
        return nullptr;
    }

    buffer = (char *)realloc(buffer, n_read + 1);
    if (buffer == nullptr) {
        free(buffer);
        close(fd);
        return nullptr;
    }

    return buffer;
}

int save_poem(const poem_t *const poem, const char *const file) {
    assert(poem);
    assert(file);

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd = creat(file, mode);
    if (fd < 0)
        return -1;

    off_t error = 0;
    size_t n_lines = poem->n_lines;
    for (size_t i = 0; i < n_lines; i++) {
        error  = write(fd, poem->lines[i].start, poem->lines[i].length);
        error += write(fd, "\n", 1);

        if (error < 0) {
            close(fd);
            return -1;
        }
    }

    close(fd);
    return 0;
}

int construct_poem(poem_t *const poem, const char *const buffer) {
    assert(poem);
    assert(buffer);

    poem->n_lines = count_lines(buffer);
    poem->lines = (line *)calloc(poem->n_lines, sizeof(line));
    if (poem->lines == nullptr)
        return -1;

    extract_lines(buffer, poem->lines);

    return 0;
}

void destruct_poem(poem_t *const poem) {
    assert(poem);

    free(poem->lines);
}

int cmp_alpha(const line line1, const line line2) {
    const char *ch1 = line1.start;
    const char *ch2 = line2.start;
    
    while (*ch1 == *ch2) {
        if (ch1 == line1.end || ch2 == line2.end)
            break;

        ch1++;
        ch2++;
    }

    return (*ch1 > *ch2) - (*ch2 > *ch1);
}

int cmp_alpha_from_end(const line line1, const line line2) {
    const char *ch1 = line1.end;
    const char *ch2 = line2.end;

    if (ch1 != line1.start || ch2 != line2.start) {
        while (*ch1 == *ch2) {
            if (ch1 == line1.start || ch2 == line2.start)
                break;

            ch1--;
            ch2--;
        }
    }

    return (*ch1 > *ch2) - (*ch2 > *ch1);
}

int cmp_alpha_punct_ignored(const line line1, const line line2) {
    const char *ch1 = line1.start;
    const char *ch2 = line2.start;
    
    while ((isspace(*ch1) || ispunct(*ch1)) && ch1 != line1.end)
        ch1++;

    while ((isspace(*ch2) || ispunct(*ch2)) && ch2 != line2.end)
        ch2++;

    while (*ch1 == *ch2) {
        if (ch1 == line1.end || ch2 == line2.end)
            break;

        ch1++;
        ch2++;
    }

    return (*ch1 > *ch2) - (*ch2 > *ch1);
}

int cmp_alpha_punct_ignored_from_end(const line line1, const line line2) {
    const char *ch1 = line1.end;
    const char *ch2 = line2.end;
    
    while (ispunct(*ch1) && ch1 != line1.start)
        ch1--;

    while (ispunct(*ch2) && ch2 != line2.start)
        ch2--;

    while (*ch1 == *ch2) {
        if (ch1 == line1.start || ch2 == line2.start)
            break;

        if (ispunct(*ch1))
            while (ispunct(*ch1) && ch1 != line1.start)
                ch1--;
        else
            ch1--;

        if (ispunct(*ch2))
            while (ispunct(*ch2) && ch2 != line2.start)
                ch2--;
        else
            ch2--;
    }

    return (*ch1 > *ch2) - (*ch2 > *ch1);
}
