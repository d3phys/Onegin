#include "include/text.h"
#include "include/onegin.h"
#include "include/config.h"
#include "include/compare.h"
#include "include/sort.h"
#include <cstdlib>

void output(FILE *file, text_t *text) {
    for (int i = 0; i < text->n_lines; i++) {
        fwrite(text->lines[i].start, sizeof(char), text->lines[i].length, file);
        fprintf(file, "\n");
    }
}

exit_code onegin_client() {
    text_t text = {0};

    construct(&text, IN_FILE_NAME);

    heap_sort(text.lines, text.n_lines, sizeof(line), compare_alphabet);

    FILE *file = fopen(OUT_FILE_NAME, "w");
    if (file == nullptr)
        return exit_code::ERR_FOPEN;

    output(file, &text);
    
    int ret_code = fclose(file);
    if (ret_code == EOF)
        return exit_code::ERR_FCLOSE;

    destruct(&text);
    return exit_code::SUCCEED;
}
