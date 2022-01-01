#include "test.h"

int Test::action(SEND_DATA * data) {
    memcpy(mainData.device,"sddfte",strlen("sddfte"));
    std::cout << "Test action" << std::endl;
    std::cout << mainData.device << std::endl;
    return 0;
}