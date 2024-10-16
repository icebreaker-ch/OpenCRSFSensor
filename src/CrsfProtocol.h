#ifndef CRSF_PROTOCOL_H
#define CRSF_PROTOCOL_H

#include <Arduino.h>
#include <stdint.h>
#include <crc8.h>

class CRSFProtocol {
    public:
        explicit CRSFProtocol(Crc8 &crc8);
        void setData(uint8_t frameType, const uint8_t *payLoad, uint8_t payLoadLen);
        void write(Stream &stream);

        static const uint16_t MAX_LEN = 64;
        static const uint8_t CRSF_POLY = 0xD5;
    
    private:
        Crc8 &crc8;
        uint8_t bufferLen;
        uint8_t buffer[MAX_LEN];
};

#endif
