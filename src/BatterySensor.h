#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <stdint.h>
#include <ICurrentSensor.h>
#include <IVoltageSensor.h>

class BatterySensor {
    public:
        static const unsigned int PAYLOAD_LEN = 8;
        static const unsigned int FRAMETYPE = 0x08;

        BatterySensor();
        void update();
        void setVoltageSensor(IVoltageSensor *pVoltageSensor);
        void setCurrentSensor(ICurrentSensor *pCurrentSensor);

        uint8_t *getPayLoad();

    private:
        static constexpr float CELL_EMPTY_VOLTS = 3.4;
        static constexpr float CELL_NORM_VOLTS = 3.7;
        static constexpr float CELL_FULL_VOLTS = 4.2;

        static const unsigned NUM_INTERPOLATION_POINTS = 9;
        static const unsigned MAX_CELLS = 12;
        
        static const float lipoVoltage[NUM_INTERPOLATION_POINTS];
        static const float lipoPercent[NUM_INTERPOLATION_POINTS];

        float voltage;
        float current;
        float capacity;
        float remaining;
        uint8_t payLoad[PAYLOAD_LEN];

        IVoltageSensor *pVoltageSensor;
        ICurrentSensor *pCurrentSensor;
        uint8_t estimateCellCount(float voltage);
        float estimateRemaining(float voltage);
};

#endif