#include "Encoder.h"

uint8_t *Encoder::encode32(uint32_t value, uint8_t *buffer) {
    *buffer++ = (value >> 24) & 0xFF;
    *buffer++ = (value >> 16) & 0xFF;
    *buffer++ = (value >> 8) & 0xFF;
    *buffer++ = value & 0xFF;
    return buffer;
}

uint8_t *Encoder::encode24(uint32_t value, uint8_t *buffer) {
    *buffer++ = (value >> 16) & 0xFF;
    *buffer++ = (value >> 8) & 0xFF;
    *buffer++ = value & 0xFF;
    return buffer;
}

uint8_t *Encoder::encode16(uint16_t value, uint8_t *buffer) {
    *buffer++ = (value >> 8) & 0xFF;
    *buffer++ = value & 0xFF;
    return buffer;
}

uint8_t *Encoder::encode8(uint8_t value, uint8_t *buffer) {
    *buffer++ = value & 0xFF;
    return buffer;
}
