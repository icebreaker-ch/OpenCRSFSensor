#include <Arduino.h>
#include "BatterySensor.h"
#include <math.h>

BatterySensor::BatterySensor() :
    voltage(0),
    current(0),
    capacity(2200),
    remaining(0) {
}

void BatterySensor::setVoltage(float voltage) {
    this->voltage = voltage;
}

uint8_t *BatterySensor::getPayLoad() {
    voltage = 12.34;
    current = 23.45;
    capacity -= 0.1;
    remaining += 0.1;

    uint16_t valVoltage = (uint16_t)(round(10.0 * voltage));
    uint16_t valCurrent = (uint16_t)(round(10.0 * current));
    uint32_t valCapacity = (uint32_t)(round(capacity));
    uint8_t valRemaining = (uint8_t)(round(remaining));

    Serial.println(valVoltage);
    Serial.println(valCurrent);
    Serial.println(valCapacity);
    Serial.println(valRemaining);
    Serial.println("---");

//    payLoad[0] = (valVoltage >> 8) && 0xFF;
    payLoad[0] = (valVoltage >> 8) & 0xFF;
    payLoad[1] = valVoltage & 0xFF;
    payLoad[2] = (valCurrent >> 8) & 0xFF;
    payLoad[3] = valCurrent & 0xFF;
    payLoad[4] = (valCapacity >> 16) & 0xFF;
    payLoad[5] = (valCapacity >> 8) & 0xFF;
    payLoad[6] = valCapacity & 0xFF;
    payLoad[7] = valRemaining;
    return payLoad;
}
