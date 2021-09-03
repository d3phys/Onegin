#include "include/onegin.h"
#include "include/config.h"
#include "include/compare.h"
#include "include/sort.h"
#include "include/error_t.h"

void output(FILE *file, text_t *text) {
    for (int i = 0; i < text->n_lines; i++) {
        fwrite(text->lines[i].start, sizeof(char), text->lines[i].length, file);
        fprintf(file, "\n");
    }
}

error_t onegin_client() {
    text_t text = {0};

    construct(&text, IN_FILE_NAME);

    heap_sort(text.lines, text.n_lines, sizeof(line), compare_alphabet);

    FILE *file = fopen(OUT_FILE_NAME, "w");
    if (file == nullptr)
        return error_t::FOPEN;

    output(file, &text);
    
    int ret_code = fclose(file);
    if (ret_code == EOF)
        return error_t::FCLOSE;

    destruct(&text);
    return error_t::SUCCESS;
}
