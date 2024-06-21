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
#ifdef BATTERY_SENSOR
static BatterySensor *pBatterySensor;
#endif

#ifdef BARO_ALTITUDE_SENSOR
static BaroAltitudeSensor *pBaroAltitudeSensor;
#endif

static GPSSensor *pGPSSensor;

void setup() {
    Serial.begin(9600);
    Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);

#ifdef BATTERY_SENSOR
    VoltageSensor *pVoltageSensor = new VoltageSensor(VOLTAGE_ANALOG_PIN, 2700, 1000);
    pVoltageSensor->setFilter(new MeanValueFilter());
    pVoltageSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    CurrentSensor *pCurrentSensor = new CurrentSensor(CURRENT_ANALOG_PIN, 0, 200);
    pCurrentSensor->setFilter(new MeanValueFilter());
    pCurrentSensor->setReportInterval(STANDARD_REPORT_INTERVAL);

    pBatterySensor = new BatterySensor();
    pBatterySensor->setVoltageSensor(pVoltageSensor);
    pBatterySensor->setCurrentSensor(pCurrentSensor);
#endif

#ifdef BARO_ALTITUDE_SENSOR
    pBaroAltitudeSensor = new BaroAltitudeSensor(new BME280());
    pBaroAltitudeSensor->setFilter(new MeanValueFilter());
    pBaroAltitudeSensor->setReportInterval(STANDARD_REPORT_INTERVAL);
#endif

#ifdef GPS_SENSOR
    pGPSSensor = new GPSSensor(new NeoGPSSensor(Serial2));
#endif
}


void loop() {
#ifdef BATTERY_SENSOR
    pBatterySensor->update();
    uint8_t *payLoad = pBatterySensor->getPayLoad();
    protocol.setData(BatterySensor::FRAMETYPE, payLoad, BatterySensor::PAYLOAD_LEN);
    protocol.write(Serial1);
#endif

#ifdef BARO_ALTITUDE_SENSOR
    pBaroAltitudeSensor->update();
    payLoad = pBaroAltitudeSensor->getPayLoad();
    protocol.setData(BaroAltitudeSensor::FRAMETYPE, payLoad, BaroAltitudeSensor::PAYLOAD_LEN);
    protocol.write(Serial1);
#endif

#ifdef GPS_SENSOR
    pGPSSensor->update();
    payLoad = pGPSSensor->getPayLoad();
    protocol.setData(GPSSensor::FRAMETYPE, payLoad, GPSSensor::PAYLOAD_LEN);
    protocol.write(Serial1);
#endif

  	delay(UPDATE_RATE);
}
