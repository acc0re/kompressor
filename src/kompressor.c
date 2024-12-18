#include <stdio.h>
#include <stdlib.h>
#include "snappy-c.h"
#include "kompressor.h"

void k_compress_file(const char* input_file, const char* output_file)
{
    // Open input file
    FILE* fp_in = fopen(input_file, "rb");
    if (!fp_in)
    {
        perror("Input file could not be opened!");
        return;
    }

    // Get the file size
    fseek(fp_in, 0, SEEK_END);
    size_t input_length = ftell(fp_in);
    fseek(fp_in, 0, SEEK_SET);

    // Allocate memory for the input data
    char* input = malloc(input_length);
    if (!input)
    {
        perror("Memory allocation failed!");
        fclose(fp_in);
        return;
    }

    // Read the file
    fread(input, 1, input_length, fp_in);
    fclose(fp_in);

    // Allocate memory for the compressed data
    size_t compressed_length = snappy_max_compressed_length(input_length);
    char* compressed = malloc(compressed_length);

    // Compress the data
    snappy_status status = snappy_compress(input, input_length, compressed, &compressed_length);
    if (status != SNAPPY_OK)
    {
        fprintf(stderr, "Compression failed!\n");
        free(input);
        free(compressed);
        return;
    }

    // Print size
    printf("Input file size: %zu Bytes\n", input_length);
    printf("Compressed file size: %to bytes\n", compressed_length);


    // Write the compressed data to the output file
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out)
    {
        perror("Output file could not be opened!");
        free(input);
        free(compressed);
        return;
    }
    fwrite(compressed, 1, compressed_length, fp_out);
    fclose(fp_out);

    printf("File ‘%s’ was compressed to ‘%s’\n", input_file, output_file);

    // Free memory
    free(input);
    free(compressed);
}

void k_decompress_file(const char* input_file, const char* output_file)
{
    // Open input file
    FILE* fp_in = fopen(input_file, "rb");
    if (!fp_in)
    {
        perror("Input file could not be opened!");
        return;
    }

    // Get the file size
    fseek(fp_in, 0, SEEK_END);
    size_t compressed_length = ftell(fp_in);
    fseek(fp_in, 0, SEEK_SET);

    // Allocate memory for the compressed data
    char* compressed = malloc(compressed_length);
    if (!compressed)
    {
        perror("Memory allocation failed!");
        fclose(fp_in);
        return;
    }

    // Read the compressed data
    fread(compressed, 1, compressed_length, fp_in);
    fclose(fp_in);

    // Get uncompressed size
    size_t uncompressed_length;
    snappy_uncompressed_length(compressed, compressed_length, &uncompressed_length);

    // Allocate memory for the uncompressed data
    char* uncompressed = malloc(uncompressed_length);
    if (!uncompressed)
    {
        perror("Memory allocation failed!");
        free(compressed);
        return;
    }

    // Decompress the data
    snappy_status status = snappy_uncompress(compressed, compressed_length, uncompressed, &uncompressed_length);
    if (status != SNAPPY_OK)
    {
        fprintf(stderr, "Decompression failed!\n");
        free(compressed);
        free(uncompressed);
        return;
    }

    // Write the decompressed data to the output file
    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out)
    {
        perror("Output file could not be opened!");
        free(compressed);
        free(uncompressed);
        return;
    }
    fwrite(uncompressed, 1, uncompressed_length, fp_out);
    fclose(fp_out);

    printf("File ‘%s’ was decompressed to ‘%s’\n", input_file, output_file);

    free(compressed);
    free(uncompressed);
}
