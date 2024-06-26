#ifndef VOLTAGE_SENSOR_H
#define VOLTAGE_SENSOR_H

#include "config.h"
#include "IVoltageSensor.h"
#include "Filter.h"
#include "Timer.h"

/**
 * A voltage measurement sensor.
 * You have to make sure to reduce the input voltage to the range [0..ANALOG_VOLTAGE_REFERENCE]
 * by using a voltage divider:
 *
 * Vin o-----.
 *           |
 *          .-.
 *          | | R1 (resistorToVoltage)
 *          | |
 *          `-'
 *           |--------o Ax (Arduino analog pin)
 *          .-.
 *          | | R2 (resistorToGround)
 *          | |
 *          `-'
 *           |
 * Gnd o-----+--------o Gnd
 *
 */
class VoltageSensor : public IVoltageSensor {
    public:
        VoltageSensor(uint8_t analogPin, long resistorToVoltage, long resistorToGround);
        void setReportInterval(unsigned long reportInterval);
        void setFilter(Filter *pFilter);
        void update() override;
        double getVoltage() override;

    private:
        uint8_t analogPin;
        long resistorToVoltage;
        long resistorToGround;
        double voltage;
        Filter *pFilter;
        Timer timer;
        unsigned long reportInterval;
};

#endif