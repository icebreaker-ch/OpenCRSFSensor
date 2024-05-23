
#include <stdint.h>
#include <math.h>
#include <Arduino.h>
#include "BaroAltitudeSensor.h"

BaroAltitudeSensor::BaroAltitudeSensor(IAltitudeSensor *pAltitudeSensor) :
    pAltitudeSensor(pAltitudeSensor),
    altitude(0.0),
    verticalSpeed(0.0),
    pFilter(nullptr),
    reportInterval(0) {
}

void BaroAltitudeSensor::update() {
    float readAltitude = pAltitudeSensor->readAltitude();
    pFilter->addValue(readAltitude);
    unsigned long elapsedTime = timer.getElapsedTime();
    if (elapsedTime >= reportInterval) {
        float newAltitude = pFilter->getFilteredValue();
        pFilter->reset();        
        verticalSpeed = 1000.0 * (newAltitude - altitude) / elapsedTime;
        altitude = newAltitude;
        timer.reset();
    }
}

uint8_t *BaroAltitudeSensor::getPayLoad() {
    uint16_t valAltitude = (uint16_t)(round(10000.0 + 10 * altitude)); /// 10000 + dm
    uint16_t valVerticalSpeed = (uint16_t)(round(100 * verticalSpeed)); // cm/s

    payLoad[0] = (valAltitude >> 8) & 0xFF;
    payLoad[1] = valAltitude & 0xFF;
    payLoad[2] = (valVerticalSpeed >> 8) & 0xFF;
    payLoad[3] = valVerticalSpeed & 0xFF;

    return payLoad;
}

void BaroAltitudeSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void BaroAltitudeSensor::setReportInterval(unsigned long reportInterval) {
    this->reportInterval = reportInterval;
}
