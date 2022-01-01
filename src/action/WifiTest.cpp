#include "WifiTest.h"

int WifiTest::action(SEND_DATA * data) {
    memcpy(mainData.device,"WifiT_Test",strlen("WifiT_Test"));
    std::cout << "WifiT_Test action" << std::endl;
    std::cout << mainData.device << std::endl;
    return 0;
}
