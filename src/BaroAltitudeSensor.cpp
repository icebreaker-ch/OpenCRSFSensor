
#include <stdint.h>
#include <math.h>
#include <Arduino.h>
#include <Encoder.h>
#include "log.h"
#include "BaroAltitudeSensor.h"

BaroAltitudeSensor::BaroAltitudeSensor(IAltitudeSensor *pAltitudeSensor) :
    calibrating(true),
    zeroAltitude(0.0),
    altitude(0.0),
    verticalSpeed(0.0),
    pAltitudeSensor(pAltitudeSensor),
    pFilter(nullptr),
    calibrationPeriod(0),
    reportInterval(0) {
}

void BaroAltitudeSensor::calibrate() {
    float readAltitude = pAltitudeSensor->readAltitude();
    pFilter->addValue(readAltitude);
    unsigned long elapsedTime = timer.getElapsedTime();
    if (elapsedTime >= calibrationPeriod) {
        zeroAltitude = pFilter->getFilteredValue();
        calibrating = false;
        pFilter->reset();
        timer.reset();
    }
}

void BaroAltitudeSensor::updateValue() {
    float readAltitude = pAltitudeSensor->readAltitude();
    pFilter->addValue(readAltitude);
    unsigned long elapsedTime = timer.getElapsedTime();
    if (elapsedTime >= reportInterval) {
        float newAltitude = pFilter->getFilteredValue() - zeroAltitude;
        pFilter->reset();
        verticalSpeed = 1000.0 * (newAltitude - altitude) / elapsedTime;
        LOG("newAltitude:", newAltitude, " verticalSpeed:", verticalSpeed, "\n");
        altitude = newAltitude;
        timer.reset();
    }
}

void BaroAltitudeSensor::update() {
    if (calibrating)
        calibrate();
    else
        updateValue();
}

uint8_t *BaroAltitudeSensor::getPayLoad() {
    uint16_t valAltitude = (uint16_t)(round(10000.0 + 10 * altitude)); /// 10000 + dm
    int16_t valVerticalSpeed = (int16_t)(round(100 * verticalSpeed)); // cm/s

    uint8_t *buffer = payLoad;
    buffer = Encoder::encode16(valAltitude, buffer);
    Encoder::encode16(valVerticalSpeed, buffer);

    return payLoad;
}

void BaroAltitudeSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void BaroAltitudeSensor::setCalibrationPeriod(unsigned long calibrationPeriod) {
    this->calibrationPeriod = calibrationPeriod;
}

void BaroAltitudeSensor::setReportInterval(unsigned long reportInterval) {
    this->reportInterval = reportInterval;
}
