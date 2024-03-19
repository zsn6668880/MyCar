#pragma once
#include <Arduino.h>
#define SERIAL_A Serial2
#define SERIAL_B Serial3
namespace Cmd{
    extern unsigned char _cmd1[8];
    extern unsigned char _cmd2[8];
    extern unsigned char _data1[8];
    extern unsigned char _data2[8];
    // extern unsigned char* _data1;
    // extern unsigned char* _data2;
    // unsigned char _cmd1[8] = {0x19, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
    // unsigned char _cmd2[8] = {0x19, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};

    void test();
    void init();
    void setCmdA(unsigned char cmdSend, long motorSpeed);
    void setCmdB(unsigned char cmdSend, long motorSpeed);
    char readDataA(unsigned char cmdSend, long* data);
    char readDataB(unsigned char cmdSend, long* data);
    char readPosA(unsigned char cmdSend, long* data);
    char readPosB(unsigned char cmdSend, long* data);
};