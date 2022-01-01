#ifndef __ISMART_H__
#define __ISMART_H__

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define TEST_CMD 0x01
#define WIFI_TEST_CMD 0x02

typedef struct SendData {
    unsigned char ip[32];
    unsigned char device[16];
    int fd;
    int cmd;
}SEND_DATA;

class ISmart {
public:
    virtual ~ISmart(){}
    virtual int action(SEND_DATA * data) = 0;
    SEND_DATA mainData;
};

#endif