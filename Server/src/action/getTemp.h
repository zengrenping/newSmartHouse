#ifndef __GET_TEMP_H__
#define __GET_TEMP_H__

#include "../../../ISmart.h"

class getTemp: public ISmart {
public:
    getTemp() {
        mainData.cmd = GET_TEMP;
    };
    int action(CLINE_DATA * data);
};

#endif