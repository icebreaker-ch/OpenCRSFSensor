#include <Arduino.h>

#include "BatterySensor.h"
#include "crc8.h"
#include "CrsfProtocol.h"

Crc8 crc(CRSFProtocol::CRSF_POLY);
CRSFProtocol protocol(crc);
BatterySensor batterySensor;

void setup() {
  Serial.begin(9600);
  Serial1.begin(420000, SERIAL_8N1, 16, 17);
}

void loop() {
  uint8_t *payLoad = batterySensor.getPayLoad();
  protocol.setData(BatterySensor::FRAMETYPE, payLoad, BatterySensor::PAYLOAD_LEN);
  Serial1.write(protocol.getBuffer(), protocol.getBufferLen());
  delay(500);
}
