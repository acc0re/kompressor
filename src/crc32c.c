#include "crc32c.h"

static uint32_t crc32c_table[256] = { /* precomputed CRC-32C table */ };

void crc32c_init(void) {
    uint32_t polynomial = 0x82F63B78;
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (uint32_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ polynomial;
            } else {
                crc = crc >> 1;
            }
        }
        crc32c_table[i] = crc;
    }
}

uint32_t crc32c(uint32_t crc, const void *buf, size_t len) {
    const uint8_t *p = (const uint8_t *)buf;
    crc = ~crc;
    while (len--) {
        crc = (crc >> 8) ^ crc32c_table[(crc ^ *p++) & 0xFF];
    }
    return ~crc;
}