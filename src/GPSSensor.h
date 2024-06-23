#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include <stdint.h>
#include "IGPSDataProvider.h"

class GPSSensor {
    public:
        static const unsigned int PAYLOAD_LEN = 15;
        static const unsigned int FRAMETYPE = 0x02;

        GPSSensor(IGPSDataProvider *pGPSDataProvider);
        void update();
        uint8_t *getPayLoad();

    private:
        IGPSDataProvider *pGPSDataProvider;
        uint8_t payLoad[PAYLOAD_LEN];
        double latitude;
        double longitude;
        double altitude;
        double speed;
        double course;
        uint8_t satteliteCount;
};

#endif
