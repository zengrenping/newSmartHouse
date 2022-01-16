#ifndef __ISMART_H__
#define __ISMART_H__

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "Socket_Server.h"

#define TEST_CMD 0x01
#define WIFI_TEST_CMD 0x02

class ISmart {
public:
    virtual ~ISmart(){}
    virtual int action(CLINE_DATA* data) = 0;
    CLINE_DATA mainData;
};

#endif