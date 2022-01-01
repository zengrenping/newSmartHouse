#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include "ISmart.h"
#include <map>

typedef struct ClinetData {
    std::string clinet_ip = "";
    int client_port = 0;
    int ClinetFd;
    char clientData[64] = {0};
    unsigned char cmd;
}CLINE_DATA;

class SocketServer {

public:
    bool creatSocket();
    bool bindSocket(unsigned short port, const char * ip);
    bool acceptSocket();

    int readData(int clientFd);
    int writeData(CLINE_DATA clientData);

    int closeSocket(int clientFd);

    int getFd() {return this->sFd;}
    void setFd();
    int getAcceptFd() {return this->acceptFd;}
    void setAcceptFd();
    // char *getData() {return data;}
    CLINE_DATA *getClinet(int acceptFd);
    std::map<int, CLINE_DATA> getClientList();

private:
    int sFd = 0;
    int acceptFd = 0;
    int clintNum = 0;
    std::map <int, CLINE_DATA> client;
    unsigned short port;
    // char data[64] = {0};

};

#endif