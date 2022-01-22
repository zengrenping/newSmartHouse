#include "../../ISmart.h"
#include "../../Socket_Server.h"
#include "../../SendHelper.h"

#include <iostream>
#include <utility>
#include <thread>

static SocketServer client;

void creatClient(unsigned short port, const char * ip) {
    if (!client.creatSocket()) {
        printf("new creatSocket is false\n");
        return;
    }
    printf("tes\n");
    if (!client.connectSocket(port, ip)) {
        printf("connect is false\n");
        return ;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("please enter 3 value.\n");
        return -1;
    }
    creatClient(atoi(argv[1]), argv[2]);
    CLINE_DATA newTest;
    const char *test = "this is test, hahahah.";
    char data[sizeof(CLINE_DATA)] = {0};
    int ret = recv(client.getFd(), &newTest, sizeof(CLINE_DATA), 0);
    if (ret < 0) {
        printf("ret < 0\n");
        return -1;
    }
    printf("ClinetFd = %d\n",newTest.ClinetFd);
    printf("data = %s\n",newTest.clientData);
    printf("clinet_ip = %s\n",newTest.clinet_ip);
    memset(&newTest.clientData, 0, sizeof(CLINE_DATA));
    strcpy(newTest.clientData, test);
    newTest.cmd = 0x01;
    while(true) {
        send(client.getFd(), &newTest, sizeof(CLINE_DATA), 0);
        sleep(5);
    }
    return 0;
}