#include <Arduino.h>
#include "FlightModeSensor.h"

FlightModeSensor::FlightModeSensor() :
    count(0) {
}

void FlightModeSensor::update() {
    ++count;
}

uint8_t *FlightModeSensor::getPayLoad() {
    sprintf((char *)payLoad, "TEST:%d", count);
    return payLoad;
}

unsigned int FlightModeSensor::getPayLoadLen() {
    return strlen((char *)payLoad) + 1;
}
