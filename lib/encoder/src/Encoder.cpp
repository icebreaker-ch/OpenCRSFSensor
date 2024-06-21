#include "Encoder.h"

void Encoder::encode32(uint32_t value, uint8_t *buffer) {
    *buffer++ = (value >> 24) & 0xFF;
    *buffer++ = (value >> 16) & 0xFF;
    *buffer++ = (value >> 8) & 0xFF;
    *buffer = value & 0xFF;
}

void Encoder::encode16(uint16_t value, uint8_t *buffer) {
    *buffer++ = (value >> 8) & 0xFF;
    *buffer = value & 0xFF;
}
