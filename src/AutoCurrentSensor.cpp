#include <Arduino.h>
#include <log.h>
#include "AutoCurrentSensor.h"
#include "CurrentSensor.h"
#include "MeanValueFilter.h"

#define SECONDS_PER_HOUR 3600.0

AutoCurrentSensor::AutoCurrentSensor(uint8_t analogPin) :
    CurrentSensor(analogPin),
    pCalibrationFilter(new MeanValueFilter()),
    calibrationPeriod(0),
    calibrating(true) {
}

void AutoCurrentSensor::calibrate() {
    double pinVoltage = readPinVoltage();
    pCalibrationFilter->addValue(pinVoltage);
    LOG("Add value: ", pinVoltage, "\n");

    unsigned long elapsedTime = timer.getElapsedTime();
    if (elapsedTime >= calibrationPeriod) {
        double filteredValue = 1000.0 * pCalibrationFilter->getFilteredValue();
        LOG("FilteredValue: ", filteredValue, "\n");
        setMilliVoltsForZeroAmps(filteredValue);
        calibrating = false;
        timer.reset();
    }
}

void AutoCurrentSensor::update() {
    if (calibrating)
        calibrate();
    else
        CurrentSensor::update();
}

void AutoCurrentSensor::setCalibrationPeriod(unsigned long calibrationPeriod) {
    this->calibrationPeriod = calibrationPeriod;
}
