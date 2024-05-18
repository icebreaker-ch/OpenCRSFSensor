#ifndef IVOLTAGE_SENSOR_H
#define IVOLTAGE_SENSOR_H

class IVoltageSensor {
    public:
        virtual double getVoltage() = 0;
};

#endif