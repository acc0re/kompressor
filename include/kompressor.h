#ifndef KOMPRESSOR_H
#define KOMPRESSOR_H

#include <stddef.h>

void k_compress_file(const char* input_file, const char* output_file);
void k_decompress_file(const char* input_file, const char* output_file);

#endif // KOMPRESSOR_H
