#ifndef __ISMART_H__
#define __ISMART_H__

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "Socket_Server.h"

#define TEST_CMD 0x01
#define GET_TEMP 0x02               //温度获取
#define SET_WATER_HEATER 0x03       //温度获取

class ISmart {
public:
    virtual ~ISmart(){}
    virtual int action(CLINE_DATA* data) = 0;
    CLINE_DATA mainData;
};

#endif