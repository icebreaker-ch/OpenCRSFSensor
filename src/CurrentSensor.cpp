#include <Arduino.h>
#include <log.h>
#include "CurrentSensor.h"

#define MILLIAMPS_PER_AMP 1000.0
#define SECONDS_PER_HOUR 3600.0

CurrentSensor::CurrentSensor(uint8_t analogPin, double millivoltsForZeroAmps, double millivoltsPerAmp) :
    analogPin(analogPin),
    millivoltsForZeroAmps(millivoltsForZeroAmps),
    millivoltsPerAmp(millivoltsPerAmp),
    current(0.0),
    consumption(0),
    pFilter(nullptr),
    reportInterval(0) {
}

void CurrentSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void CurrentSensor::update() {
    long analogReadValue = analogRead(analogPin);
    long pinMilliVolts = analogReadValue * ANALOG_REFERENCE_VOLTAGE / MAX_ANALOG_READ;
    double current = (pinMilliVolts - millivoltsForZeroAmps) / millivoltsPerAmp;

    pFilter->addValue(current);

    unsigned long elapsedTime = timer.getElapsedTime();
    if (elapsedTime >= reportInterval) {
        current = pFilter ? pFilter->getFilteredValue() : current;
        pFilter->reset();
        LOG("Reporting new Current: ", reportCurrent, "\n");

        consumption += current * elapsedTime / MILLIAMPS_PER_AMP / SECONDS_PER_HOUR;
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
