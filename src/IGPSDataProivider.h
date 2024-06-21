#ifndef IGPS_SENSOR_H
#define IGPS_SENSOR_H

class IGPSDataProvider {
    public:
        virtual void update();
        virtual uint8_t getSattelites() = 0;
        virtual double getLongitude() = 0;
        virtual double getLatitude() = 0;
        virtual double getAltitude() = 0;
        virtual double getSpeed() = 0;
        virtual double getCourse() = 0;
};

#endif