#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

class Encoder {
    public:
        static void encode32(uint32_t value, uint8_t *buffer);
        static void encode16(uint16_t value, uint8_t *buffer);
};
#endif
