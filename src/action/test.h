#ifndef __Test_H__
#define __Test_H__

#include "../ISmart.h"

class Test: public ISmart {
public:
    Test() {
        mainData.cmd = TEST_CMD;
    };
    int action(SEND_DATA * data);
};

#endif