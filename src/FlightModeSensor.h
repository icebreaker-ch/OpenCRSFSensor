#ifndef FLIGHT_MODE_SENSOR_H
#define FLIGHT_MODE_SENSOR_H

#include <stdint.h>

/**
 * This is mainly a sensor for Tests or general purpose.
 * You can transfer a String up to 13 characters plus the terminating null.
 */
class FlightModeSensor {
    public:
        static const unsigned int FRAMETYPE = 0x21;

        FlightModeSensor();
        void update();
        uint8_t *getPayLoad();
        unsigned int getPayLoadLen();
};

#endif
