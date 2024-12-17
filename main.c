#include <stdio.h>
#include <stdlib.h>
#include "snappy-c.h"

void compress_file(const char *input_file, const char *output_file) {
    // Datei öffnen
    FILE *fp_in = fopen(input_file, "rb");
    if (!fp_in) {
        perror("Eingabedatei konnte nicht geöffnet werden");
        return;
    }

    // Dateigröße bestimmen
    fseek(fp_in, 0, SEEK_END);
    size_t input_length = ftell(fp_in);
    fseek(fp_in, 0, SEEK_SET);

    // Speicher für Eingabedaten reservieren
    char *input = malloc(input_length);
    if (!input) {
        perror("Speicherzuweisung fehlgeschlagen");
        fclose(fp_in);
        return;
    }

    // Datei lesen
    fread(input, 1, input_length, fp_in);
    fclose(fp_in);

    // Speicher für komprimierte Daten reservieren
    size_t compressed_length = snappy_max_compressed_length(input_length);
    char *compressed = malloc(compressed_length);

    // Daten komprimieren
    snappy_status status = snappy_compress(input, input_length, compressed, &compressed_length);
    if (status != SNAPPY_OK) {
        fprintf(stderr, "Kompression fehlgeschlagen!\n");
        free(input);
        free(compressed);
        return;
    }

    // Komprimierte Daten in Ausgabedatei schreiben
    FILE *fp_out = fopen(output_file, "wb");
    if (!fp_out) {
        perror("Ausgabedatei konnte nicht geöffnet werden");
        free(input);
        free(compressed);
        return;
    }
    fwrite(compressed, 1, compressed_length, fp_out);
    fclose(fp_out);

    printf("Datei '%s' wurde komprimiert zu '%s'\n", input_file, output_file);

    // Speicher freigeben
    free(input);
    free(compressed);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Verwendung: %s <eingabedatei> <ausgabedatei>\n", argv[0]);
        return 1;
    }

    printf(argv[1]);

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    compress_file(input_file, output_file);

    return 0;
}
