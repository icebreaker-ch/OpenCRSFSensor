#include <Arduino.h>
#include <log.h>
#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t analogPin, long resistorToVoltage, long resistorToGround) :
    analogPin(analogPin),
    resistorToVoltage(resistorToVoltage),
    resistorToGround(resistorToGround),
    lastReportVoltage(0.0),
    pFilter(nullptr),
    reportInterval(0) {
}

void VoltageSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void VoltageSensor::setReportInterval(unsigned long reportInterval) {
    this->reportInterval = reportInterval;
}

double VoltageSensor::getVoltage() {
    int analogReadValue = analogRead(analogPin);
    double pinVoltage = (analogReadValue * ANALOG_REFERENCE_VOLTAGE) / MAX_ANALOG_READ;
    double inputVoltage = pinVoltage * (resistorToGround + resistorToVoltage) / resistorToGround;
    pFilter->addValue(inputVoltage);

    double reportVoltage;
    if (timer.getElapsedTime() >= reportInterval) {
        reportVoltage = pFilter ? pFilter->getFilteredValue() : inputVoltage;
        pFilter->reset();
        lastReportVoltage = reportVoltage;
        LOG("Reporting new Voltage: ", reportVoltage, "\n");
        timer.reset();
    } else {
        reportVoltage = lastReportVoltage;
    }

    return reportVoltage;
}