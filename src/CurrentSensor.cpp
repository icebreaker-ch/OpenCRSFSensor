#include <Arduino.h>
#include <log.h>
#include "CurrentSensor.h"

#define SECONDS_PER_HOUR 3600.0

CurrentSensor::CurrentSensor(uint8_t analogPin, double millivoltsForZeroAmps, double millivoltsPerAmp) :
    analogPin(analogPin),
    millivoltsForZeroAmps(millivoltsForZeroAmps),
    millivoltsPerAmp(millivoltsPerAmp),
    current(0.0),
    consumption(0.0),
    pFilter(nullptr),
    reportInterval(0) {
}

void CurrentSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void CurrentSensor::update() {
    uint16_t analogReadValue = analogRead(analogPin);
    double pinVoltage = analogReadValue * ANALOG_REFERENCE_VOLTAGE / MAX_ANALOG_READ;
    double readCurrent = (1000.0 * pinVoltage - millivoltsForZeroAmps) / millivoltsPerAmp;

    pFilter->addValue(readCurrent);

    unsigned long elapsedTime = timer.getElapsedTime();
    if (elapsedTime >= reportInterval) {
        current = pFilter->getFilteredValue();
        pFilter->reset();
        LOG("Reporting new Current: ", current, "\n");

        // Calculate consumption
        consumption += current * elapsedTime / SECONDS_PER_HOUR; // mAh
        timer.reset();
    }
}

void CurrentSensor::setReportInterval(unsigned long reportInterval) {
    this->reportInterval = reportInterval;
}

double CurrentSensor::getCurrent() {
    return current;
}

double CurrentSensor::getConsumption() {
    return consumption;
}
