#include <Arduino.h>
#include "CellCountDetector.h"

CellCountDetector::CellCountDetector() :
    calibrating(true),
    cellCount(0) {
}

void CellCountDetector::addVoltage(float voltage) {
    if (calibrating) {
        meanValueFilter.addValue(voltage);
        if (timer.getElapsedTime() >= calibrationPeriod) {
            float meanVoltage = meanValueFilter.getFilteredValue();
            cellCount = estimateCellCount(meanVoltage);
            calibrating = false;
        }
    }
}

void CellCountDetector::setCalibrationPeriod(unsigned long calibrationPeriod) {
    this->calibrationPeriod = calibrationPeriod;
    timer.reset();
}

bool CellCountDetector::calibrationDone() {
    return ! calibrating;
}

uint8_t CellCountDetector::getCellCount() {
    return cellCount;
}

uint8_t CellCountDetector::estimateCellCount(float voltage) {
    for (uint8_t numCells = 1; numCells <= MAX_CELLS; ++numCells) {
        if ((numCells * CELL_EMPTY_VOLTS <= voltage) && (voltage <= numCells * CELL_FULL_VOLTS)) {
            return numCells;
        }
    }
    // Strange battery voltage...
    return max((uint8_t)1, (uint8_t)(round(voltage / CELL_NORM_VOLTS)));
}
