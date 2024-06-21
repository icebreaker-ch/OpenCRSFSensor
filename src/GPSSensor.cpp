#include <math.h>
#include <Arduino.h>
#include "GPSSensor.h"

GPSSensor::GPSSensor(IGPSDataProvider *pGPSDataProvider) :
    pGPSDataProvider(pGPSDataProvider),
    latitude(0.0),
    longitude(0.0),
    altitude(0.0),
    satteliteCount(0) {
}

void GPSSensor::update() {
    pGPSDataProvider->update();
    latitude = pGPSDataProvider->getLatitude();
    longitude = pGPSDataProvider->getLongitude();
    altitude = pGPSDataProvider->getAltitude();
    satteliteCount = pGPSDataProvider->getSattelites();

    Serial.print("Sattelites: ");
    Serial.println(satteliteCount);

    Serial.print("Alt: ");
    Serial.println(altitude);
}

uint8_t *GPSSensor::getPayLoad() {
    int32_t valLatitude = int32_t(round(latitude * 1.0E7));
    int32_t valLongitude = int32_t(round(longitude * 1.0E7));
    int16_t valGroundSpeed = 0;
    int16_t valCourse = 0;
    uint16_t valAltitude = uint16_t(round(altitude + 1000.0));

    payLoad[0] = (valLatitude >> 24) & 0xFF;
    payLoad[1] = (valLatitude >> 16) & 0xFF;
    payLoad[2] = (valLatitude >> 8) & 0xFF;
    payLoad[3] = valLatitude & 0xFF;
    payLoad[4] = (valLongitude >> 24) & 0xFF;
    payLoad[5] = (valLongitude >> 16) & 0xFF;
    payLoad[6] = (valLongitude >> 8) & 0xFF;
    payLoad[7] = valLongitude & 0xFF;
    payLoad[8] = (valGroundSpeed >> 8) & 0xFF;
    payLoad[9] = valGroundSpeed  & 0xFF;
    payLoad[10] = (valCourse >> 8) & 0xFF;
    payLoad[11] = valCourse  & 0xFF;
    payLoad[12] = (valAltitude >> 8) & 0xFF;
    payLoad[13] = valAltitude  & 0xFF;
    payLoad[14] = satteliteCount;

    return payLoad;

}
