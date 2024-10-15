#include <Arduino.h>
#include "config.h"
#include "log.h"
#include "BME280.h"
#include "BaroAltitudeSensor.h"
#include "AutoCurrentSensor.h"
#include "CurrentSensor.h"
#include "BatterySensor.h"
#include "CellCountDetector.h"
#include "VoltageSensor.h"
#include "NeoGPSSensor.h"
#include "GPSSensor.h"
#include "FlightModeSensor.h"
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

#ifdef GPS_SENSOR
static GPSSensor *pGPSSensor;
#endif

#ifdef FLIGHT_MODE_SENSOR
static FlightModeSensor *pFlightModeSensor;
#endif

Stream *pCrsfStream = nullptr;

void setup() {
    pinMode(BUILTIN_LED_PORT, OUTPUT);
#ifdef CONFIGURE_ANALOG_REFERENCE_SOURCE
    analogReference(ANALOG_REFERENCE_SOURCE);
#endif

    Serial.begin(9600);

#ifdef ARDUINO_AVR_PRO
    Serial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    pCrsfStream = &Serial;
#else
#if defined(CRSF_RX_PIN) && defined(CRSF_TX_PIN)
    Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1, CRSF_RX_PIN, CRSF_TX_PIN);
    pCrsfStream = &Serial1;
#else
    Serial1.begin(CRSF_BAUDRATE);
    pCrsfStream = &Serial1;
#endif
#endif

#ifdef BATTERY_SENSOR
    VoltageSensor *pVoltageSensor = nullptr;
#endif
#ifdef VOLTAGE_SENSOR
    CellCountDetector *pCellCountDetector = nullptr;
    pCellCountDetector = new CellCountDetector();
    pCellCountDetector->setCalibrationPeriod(CALIBRATION_PERIOD);

    pVoltageSensor = new VoltageSensor(VOLTAGE_ANALOG_PIN, RESISTOR_TO_VOLTAGE, RESISTOR_TO_GROUND);
    pVoltageSensor->setFilter(new MeanValueFilter());
    pVoltageSensor->setReportInterval(STANDARD_REPORT_INTERVAL);
#endif

#ifdef BATTERY_SENSOR
    ICurrentSensor *pCurrentSensor = nullptr;
#endif
#ifdef CURRENT_SENSOR
    AutoCurrentSensor *pSensor = new AutoCurrentSensor(CURRENT_ANALOG_PIN);
    pSensor->setMilliVoltsPerAmp(MILLIVOLTS_PER_AMP);
    pSensor->setFilter(new MeanValueFilter);
    pSensor->setCalibrationPeriod(CALIBRATION_PERIOD);
    pSensor->setReportInterval(STANDARD_REPORT_INTERVAL);
    pCurrentSensor = pSensor;
#endif

#ifdef BATTERY_SENSOR
    pBatterySensor = new BatterySensor();
    pBatterySensor->setVoltageSensor(pVoltageSensor);
    pBatterySensor->setCurrentSensor(pCurrentSensor);
    pBatterySensor->setCellCountDetector(pCellCountDetector);
#endif

#ifdef BARO_ALTITUDE_SENSOR
    Wire.begin(BARO_SDA_PIN, BARO_SCL_PIN);
    pBaroAltitudeSensor = new BaroAltitudeSensor(new BME280());
    pBaroAltitudeSensor->setFilter(new MeanValueFilter());
    pBaroAltitudeSensor->setCalibrationPeriod(CALIBRATION_PERIOD);
    pBaroAltitudeSensor->setReportInterval(STANDARD_REPORT_INTERVAL);
#endif

#ifdef GPS_SENSOR
    Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    pGPSSensor = new GPSSensor(new NeoGPSSensor(Serial2));
#endif

#ifdef FLIGHT_MODE_SENSOR
    pFlightModeSensor = new FlightModeSensor();
#endif
}

void loop() {
    static bool ledState = false;
    uint8_t *payLoad;

    digitalWrite(BUILTIN_LED_PORT, ledState ? HIGH : LOW);
    ledState = !ledState;

#ifdef BATTERY_SENSOR
    pBatterySensor->update();
    payLoad = pBatterySensor->getPayLoad();
    protocol.setData(BatterySensor::FRAMETYPE, payLoad, BatterySensor::PAYLOAD_LEN);
    protocol.write(*pCrsfStream);
#endif

#ifdef BARO_ALTITUDE_SENSOR
    pBaroAltitudeSensor->update();
    payLoad = pBaroAltitudeSensor->getPayLoad();
    protocol.setData(BaroAltitudeSensor::FRAMETYPE, payLoad, BaroAltitudeSensor::PAYLOAD_LEN);
    protocol.write(*pCrsfStream);
#endif

#ifdef GPS_SENSOR
    pGPSSensor->update();
    payLoad = pGPSSensor->getPayLoad();
    protocol.setData(GPSSensor::FRAMETYPE, payLoad, GPSSensor::PAYLOAD_LEN);
    protocol.write(*pCrsfStream);
#endif

#ifdef FLIGHT_MODE_SENSOR
    pFlightModeSensor->update();
    payLoad = pFlightModeSensor->getPayLoad();
    protocol.setData(FlightModeSensor::FRAMETYPE, payLoad, pFlightModeSensor->getPayLoadLen());
    protocol.write(*pCrsfStream);
#endif
 
  	delay(UPDATE_RATE);
}
