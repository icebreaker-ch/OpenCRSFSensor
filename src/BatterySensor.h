#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

class BatterySensor {
    public:
        BatterySensor();
        void setVoltage(float voltage);

    private:
        float voltage;
        float current;
        float capacity;
        float remaining;
};

#endif