#include <Arduino.h>
#include "BatterySensor.h"
#include <math.h>
#include "log.h"

const float BatterySensor::lipoVoltage[NUM_INTERPOLATION_POINTS] = {3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2};
const float BatterySensor::lipoPercent[NUM_INTERPOLATION_POINTS] = {0.0, 8.0, 22.0, 45.0, 65.0, 80.0, 90.0, 97.0, 100.0};

BatterySensor::BatterySensor() :
    voltage(0),
    current(0),
    capacity(0),
    remaining(0),
    pVoltageSensor(nullptr),
    pCurrentSensor(nullptr) {
}

void BatterySensor::setVoltageSensor(IVoltageSensor *pVoltageSensor) {
    this->pVoltageSensor = pVoltageSensor;
}

void BatterySensor::setCurrentSensor(ICurrentSensor *pCurrentSensor) {
    this->pCurrentSensor = pCurrentSensor;
}

void BatterySensor::update() {
    pVoltageSensor->update();
    voltage = pVoltageSensor->getVoltage();
    LOG("Voltage: ", voltage, " V\n");

    pCurrentSensor->update();
    current = pCurrentSensor->getCurrent();
    LOG("Current ", current, " A\n");
    capacity = pCurrentSensor->getConsumption();
    LOG("Capacity ", capacity, " mAh\n");

    remaining = estimateRemaining(voltage);
    LOG("Remaining: ", remaining, " %\n");
}

uint8_t *BatterySensor::getPayLoad() {
    uint16_t valVoltage = (uint16_t)(round(10.0 * voltage));
    uint16_t valCurrent = (uint16_t)(round(10.0 * current));
    uint32_t valCapacity = (uint32_t)(round(capacity));
    uint8_t valRemaining = (uint8_t)(round(remaining));

    payLoad[0] = (valVoltage >> 8) & 0xFF;
    payLoad[1] = valVoltage & 0xFF;
    payLoad[2] = (valCurrent >> 8) & 0xFF;
    payLoad[3] = valCurrent & 0xFF;
    payLoad[4] = (valCapacity >> 16) & 0xFF;
    payLoad[5] = (valCapacity >> 8) & 0xFF;
    payLoad[6] = valCapacity & 0xFF;
    payLoad[7] = valRemaining;
    return payLoad;
}

uint8_t BatterySensor::estimateCellCount(float voltage) {
    for (uint8_t numCells = 1; numCells <= MAX_CELLS; ++numCells) {
        if ((numCells * CELL_EMPTY_VOLTS <= voltage) && (voltage <= numCells * CELL_FULL_VOLTS)) {
            return numCells;
        }
    }
    // Strange battery voltage...
    return max((uint8_t)1, (uint8_t)(round(voltage / CELL_NORM_VOLTS)));
}

float BatterySensor::estimateRemaining(float voltage) {
    float estimatedRemaining = 0;
    uint8_t cellCount = estimateCellCount(voltage);

    float cellVoltage = voltage / cellCount;

    if (cellVoltage < lipoVoltage[0])
        estimatedRemaining = 0;
    else if (cellVoltage > lipoVoltage[NUM_INTERPOLATION_POINTS - 1])
        estimatedRemaining = 100.0;
    else {
        for (unsigned index = 0; index < NUM_INTERPOLATION_POINTS - 2; ++index) {
            float lowerVoltage = lipoVoltage[index];
            float upperVoltage = lipoVoltage[index + 1];
            if ((lowerVoltage <= cellVoltage) && (cellVoltage <= upperVoltage)) {
                float diffVoltage = upperVoltage - lowerVoltage;
                float lowerPercentage = lipoPercent[index];
                float upperPercentage = lipoPercent[index + 1];
                float diffPercentage = upperPercentage - lowerPercentage;
                estimatedRemaining = lowerPercentage + diffPercentage * ((cellVoltage - lowerVoltage) / diffVoltage);
            }
        }
    }
    return estimatedRemaining;
}
