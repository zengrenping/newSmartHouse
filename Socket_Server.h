#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>

typedef struct ClinetData {
    char clinet_ip[16] = {0};
    int client_port = 0;
    int ClinetFd;
    char clientData[64] = {0};
    int cmd;
}CLINE_DATA;

class SocketServer {

public:
    bool creatSocket();
    bool bindSocket(unsigned short port, const char * ip);
    bool connectSocket(unsigned short port, const char * ip);
    bool acceptSocket();

    int readData(int clientFd);//服务器用
    CLINE_DATA *readData();//客户端用
    int writeData(CLINE_DATA *clientData);

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