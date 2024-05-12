#ifndef CRC8_H
#define CRC8_H

#include <stdint.h>

class Crc8 {
public:
    Crc8(uint8_t poly);
    uint8_t calc(uint8_t *data, uint8_t len);

protected:
    uint8_t lookupTable[256];
    void init(uint8_t poly);
};

#endif