#ifndef CELL_COUNT_DETECTOR_H
#define CELL_COUNT_DETECTOR_H

#include <stdint.h>
#include "Timer.h"
#include "MeanValueFilter.h"

class CellCountDetector {
    public:        
        CellCountDetector();
        void addVoltage(float voltage);
        void setCalibrationPeriod(unsigned long calibrationPeriod);
        bool calibrationDone();
        uint8_t getCellCount();

    private:
        static constexpr float CELL_EMPTY_VOLTS = 3.0;
        static constexpr float CELL_NORM_VOLTS = 3.7;
        static constexpr float CELL_FULL_VOLTS = 4.2;
        static const unsigned MAX_CELLS = 12;

        bool calibrating;
        Timer timer;
        unsigned long calibrationPeriod;
        MeanValueFilter meanValueFilter;
        uint8_t cellCount;
        uint8_t estimateCellCount(float voltage);
};

#endif
