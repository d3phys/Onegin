#include "include/onegin.h"
#include "include/compare.h"
#include "include/sort.h"
#include "include/error_t.h"
#include "include/argv.h"
#include "include/debug.h"
#include <assert.h>
#include <cstdlib>
#include <string.h>

/*
static config CONFIG = {0};

int construct_onegin_cfg(const int argc, const char *argv[]) {
    assert(argv);
    
    CONFIG.sort_func    = heap_sort;
    CONFIG.compare_func = compare_alpha;
    CONFIG.action = sort;

    int error = scan_args(argc, argv, ONEGIN_OPTIONS, 
                          sizeof(ONEGIN_OPTIONS) / sizeof(*ONEGIN_OPTIONS));

    if (error != 0) {
        return -1;
    }

    return 0;
}

int onegin_client() {
    int error = CONFIG.action();
    return error;
}
*/
/*
void output(FILE *file, const text_t *text) {
    assert(file);
    assert(text);

    size_t n_lines = text->n_lines;
    for (size_t i = 0; i < n_lines; i++) {
        fwrite(text->lines[i].start, sizeof(char), text->lines[i].length, file);
        fprintf(file, "\n");
    }
}

int onegin_client() {
    int error = CONFIG.action();
    return error;
}

int format() {
    if (CONFIG.n_output_files != 1) {
        ONEG_REPORT("There must be one out file for formatting. Files: %ld", CONFIG.n_output_files);
        return ong_exit_code::OEC_INVALID_CFG;
    }

    FILE *from = fopen(CONFIG.input_file, "r");
    if (from == nullptr) {
        ONEG_REPORT("Opening input file error: %s", CONFIG.input_file);
        return ong_exit_code::OEC_SYS_ERROR;
    }

    char *buff = nullptr;
    int error = buffer(from, &buff);
    if (error != 0)
        return ong_exit_code::OEC_INVALID_CFG;

    FILE *to = fopen(CONFIG.output_files[0], "w");
    if (to == nullptr) {
        ONEG_REPORT("Opening output file error: %s", CONFIG.output_files[0]);
        return ong_exit_code::OEC_SYS_ERROR;
    }


    error = format_text(buff, to);
    free(buff);
    if (error != 0)
        return ong_exit_code::OEC_INVALID_CFG;

    fclose(to);
    fclose(from);
    return 0;
}


int sort() {
    text_t text = {0};

    FILE *file = fopen(CONFIG.input_file, "r");
    if (file == nullptr) {
        ONEG_REPORT("Opening input file error: %s", CONFIG.input_file);
        return ong_exit_code::OEC_SYS_ERROR;
    }

    if (CONFIG.n_output_files == 0) {
        ONEG_REPORT("There are must be at least one output file. Output files count: %ld", CONFIG.n_output_files);
        return ong_exit_code::OEC_INVALID_CFG;
    }

    int error = construct_text(&text, file);
    if (error != 0) {
        if (error == text_error_t::TEXT_INVALID_FORMAT) {
            ONEG_REPORT("Bad input text format. Text lib error code: %d", error);
        }
        return ong_exit_code::OEC_INVALID_CFG;
    }

    if (ferror(file) != 0) {
        ONEG_REPORT("File stream error. File id: %ld", (size_t)file);
        return ong_exit_code::OEC_SYS_ERROR;
    }

    fclose(file);

    CONFIG.sort_func(text.lines, text.n_lines, sizeof(line), CONFIG.compare_func);

    for (size_t i = 0; i < CONFIG.n_output_files; i++) {
        file = fopen(CONFIG.output_files[i], "w");
        if (file == nullptr) {
            ONEG_REPORT("Opening output file error: %s... Next files will be ignored.", CONFIG.output_files[i]);
            return ong_exit_code::OEC_INVALID_CFG;
        }

        output(file, &text);

        if (ferror(file) != 0) {
            ONEG_REPORT("File stream error. File id: %ld", (size_t)file);
            return ong_exit_code::OEC_INVALID_CFG;
        }
        fclose(file);
    }

    destruct_text(&text);
    return 0;
}

int set_format_action(const char *args[], const size_t n_args) {
    if (n_args != 1)
        return argv_error_t::ARGV_OPTION_FAIL;

    CONFIG.action = format;

    return 0;
}

int set_cfg_output(const char *args[], const size_t n_args) {
    if (n_args < 2 || n_args > MAX_OUT_FILES + 1)
        return argv_error_t::ARGV_OPTION_FAIL;

    size_t n_out = 0;
    for (n_out = 0; n_out < n_args - 1; n_out++) {
        CONFIG.output_files[n_out] = args[n_out + 1];
    }

    CONFIG.n_output_files = n_out;

    return 0;
}

int set_cfg_input (const char *args[], const size_t n_args) {
    if (n_args != 2) {
        return argv_error_t::ARGV_OPTION_FAIL;
    }

    CONFIG.input_file = args[1];
    return 0;
}

int set_cfg_sort_func(const char *args[], const size_t n_args) {
    if (n_args != 2) {
        return argv_error_t::ARGV_OPTION_FAIL;
    }

    const char *sort = args[1];

    size_t n_algs = sizeof(ALGORITHMS) / sizeof(*ALGORITHMS);
    for (int i = 0; i < n_algs; i++)
        if (strncmp(ALGORITHMS[i].name, sort, KEYWORD_SIZE) == 0) {
            CONFIG.sort_func= ALGORITHMS[i].sort_func;
            return 0;
        }

    return argv_error_t::ARGV_OPTION_FAIL;
}

int set_cfg_comp_func(const char *args[], const size_t n_args) {
    if (n_args != 2) {
        return argv_error_t::ARGV_OPTION_FAIL;
    }

    const char *comp = args[1];

    size_t n_priorities = sizeof(PRIORITIES) / sizeof(*PRIORITIES);
    for (int i = 0; i < n_priorities; i++)
        if (strncmp(PRIORITIES[i].name, comp, KEYWORD_SIZE) == 0) {
            CONFIG.compare_func = PRIORITIES[i].compare_func;
            return 0;
        }

    return argv_error_t::ARGV_OPTION_FAIL;
}

int set_log_file(const char *args[], const size_t n_args) {
    if (n_args != 2)
        return argv_error_t::ARGV_OPTION_FAIL;

    FILE *log = fopen(args[1], "w");
    if (log == nullptr)
            return argv_error_t::ARGV_OPTION_FAIL;
    
    ONEG_LOG = log;
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
*/
