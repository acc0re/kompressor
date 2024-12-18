#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kompressor.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <compress|decompress> <input_file> <output_file>", argv[0]);
        return 1;
    }

    const char *operation = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];

    if (strcmp(operation, "compress") == 0) {
        k_compress_file(input_file, output_file);
    } else if (strcmp(operation, "decompress") == 0) {
        k_decompress_file(input_file, output_file);
    } else {
        fprintf(stderr, "Unknown operation: %s\n", operation);
        return 1;
    }

    return 0;
}
