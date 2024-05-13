#ifndef VOLTAGE_SENSOR_H
#define VOLTAGE_SENSOR_H

#include <stdint.h>


class VoltageSensor {
    public:
        VoltageSensor(uint8_t analogPin, long resistorToVoltage, long resistorToGround);
        float getVoltage();

    private:
        uint8_t analogPin;
        long resistorToVoltage;
        long resistorToGround;
};

#endif