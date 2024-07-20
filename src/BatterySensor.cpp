#include "BatterySensor.h"
#include <Encoder.h>
#include "log.h"

const float BatterySensor::lipoVoltage[NUM_INTERPOLATION_POINTS] = {3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2};
const float BatterySensor::lipoPercent[NUM_INTERPOLATION_POINTS] = {0.0, 8.0, 22.0, 45.0, 65.0, 80.0, 90.0, 97.0, 100.0};

BatterySensor::BatterySensor() :
    voltage(0),
    current(0),
    capacity(0),
    remaining(0),
    pVoltageSensor(nullptr),
    pCurrentSensor(nullptr),
    pCellCountDetector(nullptr) {
}

void BatterySensor::setVoltageSensor(IVoltageSensor *pVoltageSensor) {
    this->pVoltageSensor = pVoltageSensor;
}

void BatterySensor::setCurrentSensor(ICurrentSensor *pCurrentSensor) {
    this->pCurrentSensor = pCurrentSensor;
}

void BatterySensor::setCellCountDetector(CellCountDetector *pCellCountDetector) {
    this->pCellCountDetector = pCellCountDetector;
}

void BatterySensor::update() {
    if (pVoltageSensor) {
        pVoltageSensor->update();
        voltage = pVoltageSensor->getVoltage();
        LOG("Voltage: ", voltage, " V\n");

        pCellCountDetector->addVoltage(voltage);
        if (pCellCountDetector->calibrationDone()) {
            remaining = estimateRemaining(voltage);
            LOG("Remaining: ", remaining, " %\n");
        }
    }

    if (pCurrentSensor) {
        pCurrentSensor->update();
        current = pCurrentSensor->getCurrent();
        LOG("Current ", current, " A\n");
        capacity = pCurrentSensor->getConsumption();
        LOG("Capacity ", capacity, " mAh\n");
    }
}

uint8_t *BatterySensor::getPayLoad() {
    uint16_t valVoltage = (uint16_t)(round(10.0 * voltage));
    uint16_t valCurrent = (uint16_t)(round(10.0 * current));
    uint32_t valCapacity = (uint32_t)(round(capacity));
    uint8_t valRemaining = (uint8_t)(round(remaining));

    uint8_t *buffer = payLoad;
    buffer = Encoder::encode16(valVoltage, buffer);
    buffer = Encoder::encode16(valCurrent, buffer);
    buffer = Encoder::encode24(valCapacity, buffer);
    Encoder::encode8(valRemaining, buffer);
    return payLoad;
}

float BatterySensor::estimateRemaining(float voltage) {
    float estimatedRemaining = 0;
    uint8_t cellCount = pCellCountDetector->getCellCount();

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
