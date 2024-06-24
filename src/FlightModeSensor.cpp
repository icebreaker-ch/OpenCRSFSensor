#include <Arduino.h>
#include "FlightModeSensor.h"

FlightModeSensor::FlightModeSensor() :
    count(0) {
}

void FlightModeSensor::update() {
    ++count;
}

uint8_t *FlightModeSensor::getPayLoad() {
    sprintf(reinterpret_cast<char *>(payLoad), "TEST:%u", count);
    return payLoad;
}

unsigned int FlightModeSensor::getPayLoadLen() {
    return strlen(reinterpret_cast<char *>(payLoad)) + 1;
}
