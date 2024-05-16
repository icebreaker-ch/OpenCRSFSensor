#include <Arduino.h>
#include "BatterySensor.h"
#include <math.h>

BatterySensor::BatterySensor() :
    voltage(0),
    current(0),
    capacity(2200),
    remaining(0) {
}

void BatterySensor::setVoltage(float voltage) {
    this->voltage = voltage;
    uint8_t cellCount = estimateCellCount(voltage);
    
    if (cellCount > 0) {
        float cellVoltage = voltage / cellCount;

        if (cellVoltage < lipoVoltage[0])
            remaining = 0;
        else if (cellVoltage > lipoVoltage[NUM_LIPO_VALUES - 1])
            remaining = 100.0;
        else {
            for (unsigned index = 0; index < NUM_LIPO_VALUES -2; ++index) {
                float lowerVoltage = lipoVoltage[index];
                float upperVoltage = lipoVoltage[index + 1];
                if ((lowerVoltage <= cellVoltage) && (cellVoltage <= upperVoltage)) {
                    float lowerPercentage = lipoPercent[index];
                    float upperPercentage = lipoPercent[index + 1];
                    remaining = lowerPercentage + (upperPercentage - lowerPercentage) * ((cellVoltage - lowerVoltage) / (upperVoltage - lowerVoltage));
                }
            }
        }
    }
}

uint8_t *BatterySensor::getPayLoad() {
    current = 23.45;
    capacity = 2200.0;

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

uint8_t BatterySensor::estimateCellCount(float voltage)
{
    for (uint8_t cells = 1; cells <= 12; ++cells) {
        if ((cells * CELL_EMPTY_VOLTS <= voltage) && (voltage <= cells * CELL_FULL_VOLTS)) {
            return cells;
        }
    }
    // Strange battery voltage...
    return (uint8_t)(round(voltage / CELL_NORM_VOLTS));
}
