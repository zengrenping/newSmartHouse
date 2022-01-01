#include "Socket_Server.h"

bool SocketServer::creatSocket() {
    sFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sFd > 0) {
        printf("sFd = %d\n",sFd);
        return true;
    }
    return false;
}

bool SocketServer::bindSocket(unsigned short port, const char * ip) {
    if (sFd < 0) {
        creatSocket();
    }
    sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port); // host to network，本地字节序转换成网络字节序
    printf("ip = %s , inet_addr = %d\n", ip, (inet_addr(ip)));
    saddr.sin_addr.s_addr = inet_addr(ip);

    int ret = bind(sFd, (struct sockaddr*)&saddr, sizeof(saddr));
    if (ret != 0) {
        printf("bind is false, ret = %d, port = %d\n",ret,port);
        return false;
    }
    listen(sFd, 10);
    return true;
}

bool SocketServer::acceptSocket() {
    CLINE_DATA new_client;
    sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
    acceptFd = accept(sFd, (struct sockaddr *)&caddr, &len);
    if (acceptFd == -1) {
        printf("accept is false \n");
        return false;
    }
    //获取设备ip和端口
    if(!getpeername(acceptFd, (struct sockaddr *)&caddr, &len)) {
        new_client.ClinetFd = acceptFd;
        new_client.clinet_ip = inet_ntoa(caddr.sin_addr);
        new_client.client_port = ntohs(caddr.sin_port);
    }
    client.insert({new_client.ClinetFd, new_client});
    clintNum++;
    printf("connect is success, clinet = %d\n",clintNum);
    return true;
}

int SocketServer::readData(int clientFd) {
    int ret = -1;
    CLINE_DATA *newClient = getClinet(clientFd);
    memset(newClient->clientData, 0, sizeof(newClient->clientData));
    for(auto &i:client) {
        printf("clientFd = %d\n",i.first);
        printf("ip = %s\n", i.second.clinet_ip.c_str());
    }
    // ret = recv(clientFd, newClient, sizeof(CLINE_DATA), 0);
    ret = recv(clientFd, &newClient->cmd, sizeof(CLINE_DATA), 0);
    printf("newClient->cmd = %d\n",newClient->cmd);
    if (ret > 0) {
        return ret;
    } else if (ret == 0) {
        closeSocket(clientFd);
    }
    return ret;

}

int SocketServer::writeData(CLINE_DATA clientData) {
    send(clientData.ClinetFd, &clientData, sizeof(CLINE_DATA), 0);
    return 0;
}

int SocketServer::closeSocket(int clientFd) {
    if (client.count(clientFd) != 0) {
        close(clientFd);;
        client.erase(clientFd);
    }
    return 0;
}

void SocketServer::setFd() {

}

void SocketServer::setAcceptFd() {

}

CLINE_DATA *SocketServer::getClinet(int acceptFd) {
    if (client.count(acceptFd) != 0)
        return &client[acceptFd];
    return nullptr;
}

std::map<int, CLINE_DATA> SocketServer::getClientList() {
    return client;
}