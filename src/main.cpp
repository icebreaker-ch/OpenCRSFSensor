#include <Arduino.h>

#include "config.h"
#include "BatterySensor.h"
#include "VoltageSensor.h"
#include "crc8.h"
#include "CrsfProtocol.h"

static Crc8 crc(CRSFProtocol::CRSF_POLY);
static CRSFProtocol protocol(crc);
static VoltageSensor voltageSensor(4, 2700, 1000);
static BatterySensor batterySensor;

void setup() {
  Serial.begin(9600);
  Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  float voltage = voltageSensor.getVoltage();
  batterySensor.setVoltage(voltage);
  Serial.println(voltage);
  uint8_t *payLoad = batterySensor.getPayLoad();
  protocol.setData(BatterySensor::FRAMETYPE, payLoad, BatterySensor::PAYLOAD_LEN);
  Serial1.write(protocol.getBuffer(), protocol.getBufferLen());
  delay(500);
}
