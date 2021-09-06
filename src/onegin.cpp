#include "include/onegin.h"
#include "include/config.h"
#include "include/compare.h"
#include "include/sort.h"
#include "include/error_t.h"
#include <assert.h>

error_t onegin_cfg(config *cfg, int argc, char *argv[]) {
    assert(argv);
    assert(cfg);

    cfg->compare_func = compare_alpha;
    cfg->sort_func    = heap_sort;
    cfg->input_file   = INPUT_FILE;
    cfg->output_file  = OUTPUT_FILE;

    return SUCCESS;
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

error_t onegin_client(const config *cfg) {
    assert(cfg);

    text_t text = {0};

    FILE *file = fopen(cfg->input_file, "r");
    if (file == nullptr)
        return FOPEN;

    construct_text(&text, file);

    if (ferror(file) != 0)
        return FERROR;
    fclose(file);

    cfg->sort_func(text.lines, text.n_lines, sizeof(line), cfg->compare_func);

    file = fopen(cfg->output_file, "w");
    if (file == nullptr)
        return FOPEN;

    output(file, &text);
    destruct_text(&text);
    
    if (ferror(file) != 0)
        return FERROR;
    fclose(file);

    return SUCCESS;
}
