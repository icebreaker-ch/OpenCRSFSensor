#ifndef AUTO_CURRENT_SENSOR_H
#define AUTO_CURRENT_SENSOR_H

#include <stdint.h>
#include "config.h"
#include "CurrentSensor.h"
#include "Filter.h"
#include "Timer.h"

/**
 * An automatic calibrating current measurement sensor.
 * The sensor takes the first measured values as zero Amp reference.
 * You have to make sure to reduce the input voltage to the range [0..ANALOG_VOLTAGE_REFERENCE]
 * eventually by using a voltage divider.
 */
class AutoCurrentSensor : public CurrentSensor {
    public:
        AutoCurrentSensor(uint8_t analogPin);
        void setCalibrationPeriod(unsigned long calibrationPeriod);
        virtual void update();

    private:
        Filter *pCalibrationFilter;
        unsigned long calibrationPeriod;
        bool calibrating;

        void calibrate();
        void updateValue();
};

#endif  