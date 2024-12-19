#ifndef KOMPRESSOR_H
#define KOMPRESSOR_H

void k_write_chunk(FILE* fp, uint8_t type, const char* data, size_t length);
void k_compress_file(const char* input_file, const char* output_file);
void k_decompress_file(const char* input_file, const char* output_file);

#endif // KOMPRESSOR_H