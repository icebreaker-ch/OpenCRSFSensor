#ifndef ICURRENT_SENSOR_H
#define ICURRENT_SENSOR_H

class ICurrentSensor {
    public:
        virtual double getCurrent() = 0;
};

#endif