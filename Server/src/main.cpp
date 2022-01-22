#include "../../ISmart.h"
#include "../../Socket_Server.h"
#include "../../SendHelper.h"

#include "action/test.h"
#include "action/getTemp.h"
#include "action/setWaterHeater.h"

#include <iostream>
#include <utility>
#include <thread>
#include <queue>
#include <chrono>
#include <functional>
#include <atomic>
#include <map>
#include <mutex>
#include <condition_variable>

#include <sys/select.h>

static std::map<int, ISmart *>gActionList;
static std::queue<CLINE_DATA> gMesList;
static bool gIsTest;
static std::mutex gMes;
static std::condition_variable gCv;
static SocketServer server;

bool socketMesGet() {
    //这里可以返回socket消息队列中的Size,如果大于0 返回true
    return gMesList.size() > 0;
}

void registerHeader(ISmart * action) {
    if (action != nullptr) {
        gActionList.insert({action->mainData.cmd, action});
    } else {
        printf("registerHeader's action is null\n");
    }
}

void testWork(int list) {
    while(gIsTest) {
        // 使用大括号的方式，完成解锁操作@{
        CLINE_DATA *client = nullptr;
        {
            std::unique_lock<std::mutex> lck(gMes);
            gCv.wait(lck,socketMesGet); //等待通知
            client  = &gMesList.front();//从容器头部获取元素
            gMesList.pop();//将容器的第一个元素移除
        }
        // 使用大括号的方式，完成解锁操作@}
        if (client != nullptr) {
            ISmart * act = gActionList[client->cmd];
            if (act != nullptr) {
                act->action(client);
            } else {
                printf("act is nullptr\n");
            }
        }
    }
}

void creatServer(unsigned short port, const char * ip) {
    if (!server.creatSocket()) {
        printf("new creatSocket is false\n");
        return;
    }
    if (!server.bindSocket(port,ip)) {
        printf("bind is false\n");
        return ;
    }
}

void socketDataWork(int acceptFd) {
    //成功之后，将Client的IP、AcceptFd组包发回给Client
    int ret = server.writeData((server.getClinet(acceptFd)));
    if (ret < 0) {
        printf("server.writeData is false\n");
        return;
    }
    while(gIsTest) {
        printf("acceptFd = %d\n",acceptFd);
        if (server.readData(acceptFd) > 0) {
            //主要的内容就在这里了
            if (server.getClinet(acceptFd) != nullptr) {
                printf("socketDataWork readData = %d\n",server.getClinet(acceptFd)->cmd);
                //将读到的内容压入队列
                gMesList.push(*server.getClinet(acceptFd));
                //释放锁，发送消息通知
                std::unique_lock<std::mutex> lck(gMes);
                gCv.notify_all();
            } else {
                printf("client map have no this acceptFd %d\n",acceptFd);
                return;
            }
        } else {
            printf("connect is broken\n");
            return;
        }
    }
}

void doMesgWork(int list) {
    //等待accept成功
    while(true) {
        if(!server.acceptSocket()) {
            printf("acceptSocket is false\n");
            break;
        }
        std::thread socketData(socketDataWork, server.getAcceptFd());
        socketData.detach();
    }
}

void deleAction() {
    auto it = gActionList.cbegin();
    while (it != gActionList.cend()) {
        delete(it->second);
        it++;
    }
}

int main(int argc, char ** argv)
{
    if (argc < 3) {
        printf("please enter 3 value.\n");
        return -1;
    }

    registerHeader(new Test());
    registerHeader(new getTemp());
    registerHeader(new setWaterHeater());

    creatServer(atoi(argv[1]), argv[2]);
    gIsTest = true;

    std::thread doMesg(doMesgWork, 1);
    std::thread test(testWork, 2);

    doMesg.join();
    test.join();

    close(server.getFd());
    close(server.getAcceptFd());
    deleAction();
    return 0;
}