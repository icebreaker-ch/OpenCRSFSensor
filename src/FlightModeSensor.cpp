#include "FlightModeSensor.h"

FlightModeSensor::FlightModeSensor() {
}

void FlightModeSensor::update() {
}

uint8_t *FlightModeSensor::getPayLoad() {    
    return (uint8_t *)"TEST";
}

unsigned int FlightModeSensor::getPayLoadLen() {
    return 5;
}
