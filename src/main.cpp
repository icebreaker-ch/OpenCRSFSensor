#include <Arduino.h>

#include "config.h"
#include "BME280.h"
#include "BaroAltitudeSensor.h"
#include "CurrentSensor.h"
#include "BatterySensor.h"
#include "VoltageSensor.h"
#include "NeoGPSSensor.h"
#include "GPSSensor.h"
#include "crc8.h"
#include "CrsfProtocol.h"
#include "MeanValueFilter.h"

static Crc8 crc(CRSFProtocol::CRSF_POLY);
static CRSFProtocol protocol(crc);
static BatterySensor *pBatterySensor;
static BaroAltitudeSensor *pBaroAltitudeSensor;
static GPSSensor *pGPSSensor;

void setup() {
    Serial.begin(9600);
    Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);

    VoltageSensor *pVoltageSensor = new VoltageSensor(32, 2700, 1000);
    pVoltageSensor->setFilter(new MeanValueFilter());
    pVoltageSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    CurrentSensor *pCurrentSensor = new CurrentSensor(33, 0, 200);
    pCurrentSensor->setFilter(new MeanValueFilter());
    pCurrentSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    pBatterySensor = new BatterySensor();
    pBatterySensor->setVoltageSensor(pVoltageSensor);
    pBatterySensor->setCurrentSensor(pCurrentSensor);

    pBaroAltitudeSensor = new BaroAltitudeSensor(new BME280());
    pBaroAltitudeSensor->setFilter(new MeanValueFilter());
    pBaroAltitudeSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    pGPSSensor = new GPSSensor(new NeoGPSSensor(Serial2));
}


void loop() {
    pBatterySensor->update();
    uint8_t *payLoad = pBatterySensor->getPayLoad();
    protocol.setData(BatterySensor::FRAMETYPE, payLoad, BatterySensor::PAYLOAD_LEN);
    protocol.write(Serial1);

    pBaroAltitudeSensor->update();
    payLoad = pBaroAltitudeSensor->getPayLoad();
    protocol.setData(BaroAltitudeSensor::FRAMETYPE, payLoad, BaroAltitudeSensor::PAYLOAD_LEN);
    protocol.write(Serial1);

    pGPSSensor->update();
    payLoad = pGPSSensor->getPayLoad();
    protocol.setData(GPSSensor::FRAMETYPE, payLoad, GPSSensor::PAYLOAD_LEN);
    protocol.write(Serial1);

  	delay(50);
}
