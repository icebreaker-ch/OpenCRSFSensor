#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

class Encoder {
    public:
        static uint8_t *encode32(uint32_t value, uint8_t *buffer);
        static uint8_t *encode24(uint32_t value, uint8_t *buffer);
        static uint8_t *encode16(uint16_t value, uint8_t *buffer);
        static uint8_t *encode8(uint8_t value, uint8_t *buffer);
};
#endif
