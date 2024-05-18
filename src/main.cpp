#include <Arduino.h>

#include "config.h"
#include "CurrentSensor.h"
#include "BatterySensor.h"
#include "VoltageSensor.h"
#include "crc8.h"
#include "CrsfProtocol.h"
#include "MeanValueFilter.h"

static Crc8 crc(CRSFProtocol::CRSF_POLY);
static CRSFProtocol protocol(crc);
static BatterySensor *pBatterySensor;

void setup() {
    Serial.begin(9600);
    Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);

    VoltageSensor *pVoltageSensor = new VoltageSensor(4, 2700, 1000);
    pVoltageSensor->setFilter(new MeanValueFilter());
    pVoltageSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    CurrentSensor *pCurrentSensor = new CurrentSensor(5, 0, 40);
    pCurrentSensor->setFilter(new MeanValueFilter());
    pCurrentSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    pBatterySensor = new BatterySensor();
    pBatterySensor->setVoltageSensor(pVoltageSensor);
    pBatterySensor->setCurrentSensor(pCurrentSensor);
}

void loop() {
    pBatterySensor->update();
    uint8_t *payLoad = pBatterySensor->getPayLoad();
    protocol.setData(BatterySensor::FRAMETYPE, payLoad, BatterySensor::PAYLOAD_LEN);
    Serial1.write(protocol.getBuffer(), protocol.getBufferLen());

  	delay(500);
}
