#ifndef IVOLTAGE_SENSOR_H
#define IVOLTAGE_SENSOR_H

class IVoltageSensor {
    public:
        virtual float getVoltage() = 0;
};

#endif