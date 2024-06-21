#include <math.h>
#include <Arduino.h>
#include <Encoder.h>
#include "GPSSensor.h"

GPSSensor::GPSSensor(IGPSDataProvider *pGPSDataProvider) :
    pGPSDataProvider(pGPSDataProvider),
    latitude(0.0),
    longitude(0.0),
    altitude(0.0),
    speed(0.0),
    course(0.0),
    satteliteCount(0) {
}

void GPSSensor::update() {
    pGPSDataProvider->update();
    latitude = pGPSDataProvider->getLatitude();
    longitude = pGPSDataProvider->getLongitude();
    altitude = pGPSDataProvider->getAltitude();
    speed = pGPSDataProvider->getSpeed();
    course = pGPSDataProvider->getCourse();
    satteliteCount = pGPSDataProvider->getSattelites();
}

uint8_t *GPSSensor::getPayLoad() {
    int32_t valLatitude = int32_t(round(latitude * 1.0E7));
    int32_t valLongitude = int32_t(round(longitude * 1.0E7));
    int16_t valGroundSpeed = int16_t(round(speed) * 10.0);
    int16_t valCourse = int16_t(round(course * 100.0));
    uint16_t valAltitude = uint16_t(round(altitude + 1000.0));

    uint8_t *buffer = payLoad;
    buffer = Encoder::encode32(valLatitude, buffer);
    buffer = Encoder::encode32(valLongitude, buffer);
    buffer = Encoder::encode16(valGroundSpeed, buffer);
    buffer = Encoder::encode16(valCourse, buffer);
    buffer = Encoder::encode16(valAltitude, buffer);
    Encoder::encode8(satteliteCount, buffer);

    return payLoad;
}
