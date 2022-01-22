#ifndef __SET_WATER_HEATER_H__
#define __SET_WATER_HEATER_H__

#include "../../../ISmart.h"

class setWaterHeater: public ISmart {
public:
    setWaterHeater() {
        mainData.cmd = SET_WATER_HEATER;
    };
    int action(CLINE_DATA * data);
};

#endif