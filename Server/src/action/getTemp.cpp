#include "getTemp.h"

int getTemp::action(CLINE_DATA * data) {
    printf("Is getTemp\n");
    printf("data.ip = %s\n", data->clinet_ip);
    printf("data.data = %s\n", data->clientData);
    return 0;
}