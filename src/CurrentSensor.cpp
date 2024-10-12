#include <Arduino.h>
#include <log.h>
#include "CurrentSensor.h"

#define SECONDS_PER_HOUR 3600.0

CurrentSensor::CurrentSensor(uint8_t analogPin):
    analogPin(analogPin),
    milliVoltsForZeroAmps(0.0),
    milliVoltsPerAmp(0.0),
    current(0.0),
    consumption(0.0),
    pFilter(nullptr),
    reportInterval(0) {
}

void CurrentSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void CurrentSensor::update() {
    double pinVoltage = readPinVoltage();
    double readCurrent = (1000.0 * pinVoltage - milliVoltsForZeroAmps) / milliVoltsPerAmp;

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

void CurrentSensor::setMilliVoltsForZeroAmps(double milliVoltsForZeroAmps) {
    this->milliVoltsForZeroAmps = milliVoltsForZeroAmps;
}

void CurrentSensor::setMilliVoltsPerAmp(double milliVoltsPerAmp) {
    this->milliVoltsPerAmp = milliVoltsPerAmp;
}

void CurrentSensor::setReportInterval(unsigned long reportInterval)
{
    this->reportInterval = reportInterval;
}

double CurrentSensor::getCurrent() {
    return current;
}

double CurrentSensor::getConsumption() {
    return consumption;
}

double CurrentSensor::readPinVoltage() {
    uint16_t analogReadValue = analogRead(analogPin);
    return analogReadValue * (ANALOG_REFERENCE_VOLTAGE / 1000.0)  / MAX_ANALOG_READ;
}
