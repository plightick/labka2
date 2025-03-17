#include "header.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Use: %s <name_file>\n", argv[0]);
        return 1;
    }

    fillingOutTheFile (argv[1]);
    
    return 0;
}