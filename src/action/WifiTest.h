#ifndef __WIFITEST_H__
#define __WIFITEST_H__

#include "../ISmart.h"

class WifiTest: public ISmart {
public:
    WifiTest() {
        mainData.cmd = WIFI_TEST_CMD;
    };
    int action(SEND_DATA * data);
};

#endif