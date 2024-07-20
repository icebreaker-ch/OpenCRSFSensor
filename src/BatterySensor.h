#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <stdint.h>
#include <ICurrentSensor.h>
#include <IVoltageSensor.h>
#include "CellCountDetector.h"

class BatterySensor {
    public:
        static const unsigned int PAYLOAD_LEN = 8;
        static const unsigned int FRAMETYPE = 0x08;

        BatterySensor();
        void update();
        void setVoltageSensor(IVoltageSensor *pVoltageSensor);
        void setCurrentSensor(ICurrentSensor *pCurrentSensor);
        void setCellCountDetector(CellCountDetector *pCellCountDetector);

        uint8_t *getPayLoad();

    private:
        static const unsigned NUM_INTERPOLATION_POINTS = 9;
        static const float lipoVoltage[NUM_INTERPOLATION_POINTS];
        static const float lipoPercent[NUM_INTERPOLATION_POINTS];

        float voltage;
        float current;
        float capacity;
        float remaining;
        uint8_t payLoad[PAYLOAD_LEN];

        IVoltageSensor *pVoltageSensor;
        ICurrentSensor *pCurrentSensor;
        CellCountDetector *pCellCountDetector;
        uint8_t estimateCellCount(float voltage);
        float estimateRemaining(float voltage);
};

#endif