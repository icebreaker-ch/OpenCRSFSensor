#include "CrsfProtocol.h"
#include <string.h>

#define POS_SYNC 0
#define POS_LEN  1
#define POS_TYPE 2
#define START_PAYLOAD 3

#define CRSF_SYNC_BYTE 0xC8
#define CRSF_CRC_POLY 0xD5

CRSFProtocol::CRSFProtocol(Crc8 &crc8) :
    crc8(crc8),
    bufferLen(0) {
        memset(buffer, '\000', CRSFProtocol::MAX_LEN);
}

void CRSFProtocol::setData(uint8_t frameType, const uint8_t *payLoad, uint8_t payLoadLen)
{
    buffer[POS_SYNC] = CRSF_SYNC_BYTE;
    buffer[POS_LEN] = payLoadLen + 2;
    buffer[POS_TYPE] = frameType;
    memcpy(&buffer[START_PAYLOAD], payLoad,payLoadLen);
    buffer[payLoadLen + 3] = crc8.calc(&buffer[POS_TYPE], payLoadLen + 1);
    bufferLen = payLoadLen + 4;
}

void CRSFProtocol::write(Stream &stream) {
    while (stream.availableForWrite() < bufferLen) {
      delay(10);
    }
    stream.write(buffer, bufferLen);
}
