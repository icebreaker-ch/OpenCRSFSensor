#include <Arduino.h>
#include "config.h"
#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t analogPin, long resistorToVoltage, long resistorToGround) :
    analogPin(analogPin),
    resistorToVoltage(resistorToVoltage),
    resistorToGround(resistorToGround) {
        pinMode(analogPin, ANALOG);
}

float VoltageSensor::getVoltage() {
    uint16_t readValue = analogRead(analogPin);
    float voltage = (REFERENCE_VOLTAGE * readValue) / MAX_ANALOG_READ;
    voltage = voltage * (resistorToGround + resistorToVoltage) / resistorToGround;
    return voltage;
}
