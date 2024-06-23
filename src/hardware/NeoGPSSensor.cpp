#include "config.h"
#include "NeoGPSSensor.h"

NeoGPSSensor::NeoGPSSensor(Stream &stream) :
    stream(stream) {
}

void NeoGPSSensor::update() {
    while (stream.available() > 0) {
        char c = stream.read();
        gps.encode(c);
    }
}

uint8_t NeoGPSSensor::getSattelites() {
    return gps.satellites.isValid() && gps.satellites.age() < SENSOR_TIMEOUT ? gps.satellites.value() : 0;
}

double NeoGPSSensor::getLongitude() {
    return gps.location.isValid() && gps.location.age() < SENSOR_TIMEOUT ? gps.location.lng() : 0;
}

double NeoGPSSensor::getLatitude() {
    return gps.location.isValid() && gps.location.age() < SENSOR_TIMEOUT ? gps.location.lat() : 0;
}

double NeoGPSSensor::getAltitude() {
    return gps.altitude.isValid() && gps.altitude.age() < SENSOR_TIMEOUT ? gps.altitude.meters() : 0;
}

double NeoGPSSensor::getSpeed() {
    return gps.speed.isValid() && gps.speed.age() < SENSOR_TIMEOUT ? gps.speed.kmph() : 0;
}

double NeoGPSSensor::getCourse() {
    return gps.course.isValid() && gps.course.age() < SENSOR_TIMEOUT ? gps.course.deg() : 0;
}
