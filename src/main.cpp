#include "include/onegin.h"

int main(const int argc, const char *argv[]) {
    if (construct_onegin_cfg(argc, argv) == 0)
        onegin_client();

    return 0;
}
