#ifndef CRSF_PROTOCOL_H
#define CRSF_PROTOCOL_H

#include <stdint.h>
#include <crc8.h>

#define MAX_LEN 64

class CRSFProtocol {
    public:
        CRSFProtocol(Crc8 &crc8);
        void setData(uint8_t frameType, uint8_t *payLoad, uint8_t payLoadLen);
        uint8_t getBufferLen();
        const uint8_t *getBuffer();

        static const uint8_t CRSF_POLY = 0xD5;
    
    private:
        Crc8 &crc8;
        uint8_t bufferLen;
        uint8_t buffer[MAX_LEN];
};

#endif
