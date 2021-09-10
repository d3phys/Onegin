#include "include/onegin.h"
#include "include/compare.h"
#include "include/sort.h"
#include "include/error_t.h"
#include "include/argv.h"
#include <assert.h>
#include <string.h>

#define ERROR_DISPLAY

const char HELP_MESSAGE[] = "------------------------------------------------------------------\n"
                            "-h|-help                                   - print this message.  \n"
                            "-i|-input   <file name>                    - set input file.      \n"
                            "-o|-output  <file names>                   - set output files.    \n"
                            "-s|-sort    heap(default)/bubble/insertion - set sort algorithm. \n"
                            "-c|-compare alpha(default)/alphar          - set compare priority.\n"
                            "------------------------------------------------------------------\n"
                            "Check README to see the details.\n";

static config CFG = {0};

int construct_onegin_cfg(const int argc, const char *argv[]) {
    assert(argv);
    
    CFG.n_output_files = 1;
    CFG.sort_func      = heap_sort;
    CFG.compare_func   = compare_alpha;

    int error = scan_args(argc, argv, ONEGIN_OPTIONS, 
                          sizeof(ONEGIN_OPTIONS) / sizeof(*ONEGIN_OPTIONS));

    return error;
}

void output(FILE *file, const text_t *text) {
    assert(file);
    assert(text);

    size_t n_lines = text->n_lines;
    for (size_t i = 0; i < n_lines; i++) {
        fwrite(text->lines[i].start, sizeof(char), text->lines[i].length, file);
        fprintf(file, "\n");
    }
}


#define SHOW_ERROR(error) printf("\u001b[31m%s\nFailed.\u001b[0m\n", error);

int onegin_client() {
    text_t text = {0};

    FILE *file = fopen(CFG.input_file, "r");
    if (file == nullptr) {
#ifdef ERROR_DISPLAY
        SHOW_ERROR("Opening input file error.");
#endif
        return FOPEN;
    }

    construct_text(&text, file);

    if (ferror(file) != 0) {
#ifdef ERROR_DISPLAY
        SHOW_ERROR("File stream error.");
#endif
        return FERROR;
    }
    fclose(file);

    CFG.sort_func(text.lines, text.n_lines, sizeof(line), CFG.compare_func);

    for (size_t i = 0; i < CFG.n_output_files; i++) {
        file = fopen(CFG.output_files[i], "w");
        if (file == nullptr) {
#ifdef ERROR_DISPLAY
        SHOW_ERROR("Opening output file error. Undefined behavior.");
#endif
            return FOPEN;
        }

        output(file, &text);

        if (ferror(file) != 0) {
#ifdef ERROR_DISPLAY
        SHOW_ERROR("File stream error.");
#endif
            return FERROR;
        }
        fclose(file);
    }

    destruct_text(&text);

    return 0;
}

int set_cfg_output(const char *args[], const size_t n_args) {
    if (n_args < 2)
        return -1;

    size_t n_out = 0;
    for (n_out = 0; n_out < n_args - 1; n_out++) {
        CFG.output_files[n_out] = args[n_out + 1];
    }

    CFG.n_output_files = n_out;

    return 0;
}

int set_cfg_input (const char *args[], const size_t n_args) {
    if (n_args < 2)
        return -1;

    CFG.input_file = args[1];
    return 0;
}

int set_cfg_sort_func(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    const size_t sort_name_size = 10;
    const char *sort = args[1];

    if (strncmp("heap", sort, sort_name_size) == 0)
        CFG.sort_func = heap_sort;
    else if (strncmp("bubble", sort, sort_name_size) == 0)
        CFG.sort_func = bubble_sort;
    else if (strncmp("insertion", sort, sort_name_size) == 0)
        CFG.sort_func = insertion_sort;
    else
        return -1;

    return 0;
}

int set_cfg_comp_func(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    const size_t comp_name_size = 10;
    const char *comp = args[1];

    if (strncmp("alpha", comp, comp_name_size) == 0)
        CFG.compare_func = compare_alpha;
    else if (strncmp("alphar", comp, comp_name_size) == 0)
        CFG.compare_func = compare_alpha_rev;
    else
        return -1;

    return 0;
}

int show_onegin_help(const char *args[], const size_t n_args) {
    printf("%s", HELP_MESSAGE);
    return 0;
}

