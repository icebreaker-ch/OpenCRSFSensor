#include <stdint.h>
#include "IAltitudeSensor.h"
#include "Filter.h"
#include "Timer.h"

class BaroAltitudeSensor {
    public:
        static const unsigned int PAYLOAD_LEN = 4;
        static const unsigned int FRAMETYPE = 0x09;

        explicit BaroAltitudeSensor(IAltitudeSensor *pAltitudeSensor);
        void update();
        uint8_t *getPayLoad();
        void setFilter(Filter *pFilter);
        void setCalibrationPeriod(unsigned long calibrationPeriod);
        void setReportInterval(unsigned long reportInterval);

    private:
        bool calibrating;
        float zeroAltitude;
        float altitude;
        float verticalSpeed;
        uint8_t payLoad[PAYLOAD_LEN];
        IAltitudeSensor *pAltitudeSensor;
        Filter *pFilter;
        unsigned long calibrationPeriod;
        unsigned long reportInterval;
        Timer timer;

        void calibrate();
        void updateValue();

};