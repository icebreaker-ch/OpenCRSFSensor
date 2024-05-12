#include "BatterySensor.h"

BatterySensor::BatterySensor() :
    voltage(0),
    current(0),
    capacity(0),
    remaining(0) {
}

void BatterySensor::setVoltage(float voltage) {
    this->voltage = voltage;
}