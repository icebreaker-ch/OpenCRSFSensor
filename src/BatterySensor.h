#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <stdint.h>

class BatterySensor {
    public:
        BatterySensor();
        void setVoltage(float voltage);
        uint8_t *getPayLoad();

        static const unsigned int PAYLOAD_LEN = 8;
        static const unsigned int FRAMETYPE = 0x08;
        static const float CELL_EMPTY_VOLTS = 3.3;
        static const float CELL_NORM_VOLTS = 3.7;
        static const float CELL_FULL_VOLTS = 4.2;


    private:
        uint8_t estimateCellCount(float voltage);

        float voltage;
        float current;
        float capacity;
        float remaining;
        uint8_t payLoad[PAYLOAD_LEN];
};

#endif