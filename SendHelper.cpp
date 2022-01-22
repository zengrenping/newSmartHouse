
#include "SendHelper.h"

bool SendHelper::sendMesg(CLINE_DATA *mesg, int flag) {
    if (mesg != nullptr) {
        int ret = send(mesg->ClinetFd, mesg, sizeof(CLINE_DATA), flag);
        if (ret > 0) {
            return true;
        }
    }
    return false;
}

SendHelper& SendHelper::getInstance() {
    static SendHelper Instatance;
    return Instatance;
}
