#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

class BatterySensor {
    public:
        BatterySensor();

    private:
        float voltage;
        float current;
        float capacity;
        float remaining;
};

#endif