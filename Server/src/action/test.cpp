#include "test.h"

int Test::action(CLINE_DATA * data) {
    std::cout << "Test action" << std::endl;
    printf("data.ip = %s\n", data->clinet_ip);
    printf("data.prot = %d\n", data->client_port);
    printf("data.data = %s\n", data->clientData);
    return 0;
}