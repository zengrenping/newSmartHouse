#ifndef __SEND_HELPER_H__
#define __SEND_HELPER_H__

#include "Socket_Server.h"

class SendHelper {
private:
    SendHelper(){};
public:
    bool sendMesg(CLINE_DATA *mesg, int flag);
    static SendHelper& getInstance();
};

#endif