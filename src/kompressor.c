#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "snappy-c.h"
#include "kompressor.h"
#include "crc32c.h"

#define CHUNK_SIZE 64 * 1024 // 64 KiB

void k_write_chunk(FILE* fp, uint8_t type, const char* data, size_t length) {
    uint32_t crc = crc32c(0, data, length);
    uint8_t header[4] = { type, length & 0xFF, (length >> 8) & 0xFF, (length >> 16) & 0xFF };
    fwrite(header, 1, 4, fp);
    fwrite(&crc, 1, 4, fp);
    fwrite(data, 1, length, fp);
}

void k_compress_file(const char* input_file, const char* output_file) {
    FILE* fp_in = fopen(input_file, "rb");
    if (!fp_in) {
        perror("Input file could not be opened!");
        return;
    }

    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        perror("Output file could not be opened!");
        fclose(fp_in);
        return;
    }

    // Write stream identifier
    const char* stream_id = "sNaPpY";
    k_write_chunk(fp_out, 0xFF, stream_id, strlen(stream_id));

    char* input = malloc(CHUNK_SIZE);
    char* compressed = malloc(snappy_max_compressed_length(CHUNK_SIZE));
    if (!input || !compressed) {
        perror("Memory allocation failed!");
        fclose(fp_in);
        fclose(fp_out);
        free(input);
        free(compressed);
        return;
    }

    size_t read_bytes;
    while ((read_bytes = fread(input, 1, CHUNK_SIZE, fp_in)) > 0) {
        size_t compressed_length = snappy_max_compressed_length(read_bytes);
        snappy_status status = snappy_compress(input, read_bytes, compressed, &compressed_length);
        if (status != SNAPPY_OK) {
            fprintf(stderr, "Compression failed!\n");
            break;
        }
        k_write_chunk(fp_out, 0x00, compressed, compressed_length);
    }

    free(input);
    free(compressed);
    fclose(fp_in);
    fclose(fp_out);
}

void k_decompress_file(const char* input_file, const char* output_file) {
    FILE* fp_in = fopen(input_file, "rb");
    if (!fp_in) {
        perror("Input file could not be opened!");
        return;
    }

    FILE* fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        perror("Output file could not be opened!");
        fclose(fp_in);
        return;
    }

    char* compressed = malloc(CHUNK_SIZE);
    char* uncompressed = malloc(snappy_max_compressed_length(CHUNK_SIZE));
    if (!compressed || !uncompressed) {
        perror("Memory allocation failed!");
        fclose(fp_in);
        fclose(fp_out);
        free(compressed);
        free(uncompressed);
        return;
    }

    uint8_t header[4];
    while (fread(header, 1, 4, fp_in) == 4) {
        uint8_t type = header[0];
        size_t length = header[1] | (header[2] << 8) | (header[3] << 16);
        uint32_t crc;
        fread(&crc, 1, 4, fp_in);
        fread(compressed, 1, length, fp_in);

        if (type == 0xFF) {
            // Stream identifier, skip
            continue;
        } else if (type == 0x00) {
            size_t uncompressed_length;
            snappy_uncompressed_length(compressed, length, &uncompressed_length);
            snappy_status status = snappy_uncompress(compressed, length, uncompressed, &uncompressed_length);
            if (status != SNAPPY_OK) {
                fprintf(stderr, "Decompression failed!\n");
                break;
            }
            fwrite(uncompressed, 1, uncompressed_length, fp_out);
        } else {
            fprintf(stderr, "Unknown chunk type: %02x\n", type);
            break;
        }
    }

    free(compressed);
    free(uncompressed);
    fclose(fp_in);
    fclose(fp_out);
}