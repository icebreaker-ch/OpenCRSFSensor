#ifndef ICURRENT_SENSOR_H
#define ICURRENT_SENSOR_H

class ICurrentSensor {
    public:
        virtual void update() = 0; 
        virtual double getCurrent() = 0;
        virtual double getConsumption() = 0;
};

#endif