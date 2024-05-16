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
        static constexpr float CELL_EMPTY_VOLTS = 3.4;
        static constexpr float CELL_NORM_VOLTS = 3.7;
        static constexpr float CELL_FULL_VOLTS = 4.2;


    private:
        uint8_t estimateCellCount(float voltage);
        static const unsigned NUM_LIPO_VALUES = 9;
        
        const float lipoVoltage[NUM_LIPO_VALUES] = {3.4,3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2};
        const float lipoPercent[NUM_LIPO_VALUES] = {0.0, 8.0, 22.0, 45.0, 65.0, 80.0, 90.0, 97.0, 100.0};

        float voltage;
        float current;
        float capacity;
        float remaining;
        uint8_t payLoad[PAYLOAD_LEN];
};

#endif