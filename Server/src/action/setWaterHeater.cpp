#include "setWaterHeater.h"

int setWaterHeater::action(CLINE_DATA * data) {
    printf("Is setWaterHeater\n");
    printf("data.ip = %s\n", data->clinet_ip);
    printf("data.data = %s\n", data->clientData);
    return 0;
}