#include "WifiTest.h"

int WifiTest::action(CLINE_DATA * data) {
    std::cout << "WifiT_Test action" << std::endl;
    printf("data.ip = %s\n", data->clinet_ip);
    printf("data.prot = %d\n", data->client_port);
    printf("data.data = %s\n", data->clientData);
    return 0;
}
