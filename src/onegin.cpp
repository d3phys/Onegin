#include "include/onegin.h"
#include "include/compare.h"
#include "include/sort.h"
#include "include/error_t.h"
#include "include/argv.h"
#include <assert.h>
#include <string.h>

#define ERROR_DISPLAY

FILE *LOG = stdout;

static config CFG = {0};

int construct_onegin_cfg(const int argc, const char *argv[]) {
    assert(argv);
    
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
        fwrite(text->lines[i].start, sizeof(char), text->lines[i].length, file);//warning
        fprintf(file, "\n");
    }
}


#define LOG_ERROR(error) fprintf(LOG, "%s\nFailed.\n", error);//log file fflush + -- ignore options

int onegin_client() {
    text_t text = {0};

    fflush(LOG);
    FILE *file = fopen(CFG.input_file, "r");
    if (file == nullptr) {
#ifdef ERROR_DISPLAY
        LOG_ERROR("Opening input file error.");
#endif
        return FOPEN;
    }

    construct_text(&text, file);

    if (ferror(file) != 0) {
#ifdef ERROR_DISPLAY
        LOG_ERROR("File stream error.");
#endif
        return FERROR;
    }
    fclose(file);

    CFG.sort_func(text.lines, text.n_lines, sizeof(line), CFG.compare_func);

    for (size_t i = 0; i < CFG.n_output_files; i++) {
        file = fopen(CFG.output_files[i], "w");
        if (file == nullptr) {
#ifdef ERROR_DISPLAY
        LOG_ERROR("Opening output file error. Undefined behavior.");
        fflush(LOG);
#endif
            return FOPEN;
        }

        output(file, &text);

        if (ferror(file) != 0) {
#ifdef ERROR_DISPLAY
        LOG_ERROR("File stream error.");
#endif
            return FERROR;
        }
        fclose(file);
    }

    destruct_text(&text);

    fclose(LOG);
    return 0;
}

int set_cfg_output(const char *args[], const size_t n_args) {
    if (n_args < 2 || n_args > MAX_OUT_FILES + 1)
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

    const char *sort = args[1];

    size_t n_algs = sizeof(ALGORITHMS) / sizeof(*ALGORITHMS);
    for (int i = 0; i < n_algs; i++)
        if (strncmp(ALGORITHMS[i].name, sort, KEYWORD_SIZE) == 0) {
            CFG.sort_func= ALGORITHMS[i].sort_func;
            return 0;
        }

    return -1;
}

int set_cfg_comp_func(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    const char *comp = args[1];

    size_t n_priorities = sizeof(PRIORITIES) / sizeof(*PRIORITIES);
    for (int i = 0; i < n_priorities; i++)
        if (strncmp(PRIORITIES[i].name, comp, KEYWORD_SIZE) == 0) {
            CFG.compare_func = PRIORITIES[i].compare_func;
            return 0;
        }

    return -1;
}

int set_log_file(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return -1;

    fflush(LOG);
    FILE *log = fopen(args[1], "w");
    if (log == nullptr)
            return -1;
    
    LOG = log;
    return 0;
}

int show_onegin_help(const char *args[], const size_t n_args) {
    size_t n_options = sizeof(ONEGIN_OPTIONS) / sizeof(*ONEGIN_OPTIONS);
    for (size_t i = 0; i < n_options; i++) {
        printf("-%c | -%-*s - %-*s\n", ONEGIN_OPTIONS[i].short_keword, 
                (int)KEYWORD_SIZE,     ONEGIN_OPTIONS[i].keyword,
                (int)DESCRIPTION_SIZE, ONEGIN_OPTIONS[i].description);
    }
    return 0;
}

