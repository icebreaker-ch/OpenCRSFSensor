#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include <stdint.h>
#include "config.h"
#include "ICurrentSensor.h"
#include "Filter.h"
#include "Timer.h"

/**
 * A current measurement sensor.
 * You have to make sure to reduce the input voltage to the range [0..ANALOG_VOLTAGE_REFERENCE]
 * eventually by using a voltage divider.
 */
class CurrentSensor : public ICurrentSensor {
    public:
        CurrentSensor(uint8_t analogPin);
        void setMilliVoltsForZeroAmps(double milliVoltsForZeroAmps);
        void setMilliVoltsPerAmp(double milliVoltsPerAmp);
        void setReportInterval(unsigned long reportInterval);
        void setFilter(Filter *pFilter);
        virtual void update() override;
        double getCurrent() override;
        double getConsumption() override;

    protected:
        Timer timer;
        double readPinVoltage();

    private:
        uint8_t analogPin;
        double milliVoltsForZeroAmps;
        double milliVoltsPerAmp;
        double current; // A
        double consumption; // mAh
        Filter *pFilter;
        unsigned long reportInterval;
};

#endif  