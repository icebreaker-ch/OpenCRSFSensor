#include <Arduino.h>
#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t analogPin, long resistorToVoltage, long resistorToGround) :
    analogPin(analogPin),
    resistorToVoltage(resistorToVoltage),
    resistorToGround(resistorToGround) {
}

float VoltageSensor::getVoltage() {
    uint16_t readValue = analogRead(analogPin);
    float voltage = (3.3 * readValue) / 4096.0;
    return voltage;
}
