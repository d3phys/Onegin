#include <assert.h>
#include "include/io.h"

int set_text_color(color text) {
    return printf("\u001b[3%dm", text);
}

int set_back_color(color background) {
    return printf("\u001b[4%dm", background);
}

int reset_color() {
    return printf("\u001b[0m");
}
