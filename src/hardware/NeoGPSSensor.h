#ifndef NEO_GPS_SENSOR_H
#define NEO_GPS_SENSOR_H

#include "config.h"
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include "IGPSDataProivider.h"

class NeoGPSSensor : public IGPSDataProvider {
    public:
        explicit NeoGPSSensor(HardwareSerial &serial);
        void update();
        uint8_t getSattelites() override;
        double getLongitude() override;
        double getLatitude() override;
        double getAltitude() override;
        double getSpeed() override;
        double getCourse() override;

    private:
        HardwareSerial &serial;
        TinyGPSPlus gps;
};

#endif