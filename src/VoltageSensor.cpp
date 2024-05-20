#include <Arduino.h>
#include <log.h>
#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t analogPin, long resistorToVoltage, long resistorToGround) :
    analogPin(analogPin),
    resistorToVoltage(resistorToVoltage),
    resistorToGround(resistorToGround),
    voltage(0.0),
    pFilter(nullptr),
    reportInterval(0) {
}

void VoltageSensor::setFilter(Filter *pFilter) {
    this->pFilter = pFilter;
}

void VoltageSensor::setReportInterval(unsigned long reportInterval) {
    this->reportInterval = reportInterval;
}

void VoltageSensor::update() {
    int analogReadValue = analogRead(analogPin);
    double pinVoltage = (analogReadValue * ANALOG_REFERENCE_VOLTAGE) / MAX_ANALOG_READ;
    double inputVoltage = pinVoltage * (resistorToGround + resistorToVoltage) / resistorToGround;
    pFilter->addValue(inputVoltage);

    if (timer.getElapsedTime() >= reportInterval) {
        voltage = pFilter->getFilteredValue();
        pFilter->reset();
        LOG("Reporting new Voltage: ", voltage, "\n");
        timer.reset();
    }
}

double VoltageSensor::getVoltage() {
    return voltage;
}