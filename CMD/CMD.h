#pragma once
#include <Arduino.h>
#define SERIAL_A Serial2
#define SERIAL_B Serial3
#define ACC 3000
#define DEC 3000
#define MAXSPEED 6000
#define LAP_A 260000
#define LAP_B 260000

namespace Cmd{

    extern unsigned char _cmd1[8];
    extern unsigned char _cmd2[8];
    extern unsigned char _data1[8];
    extern unsigned char _data2[8];
   
    void init();
    void setCmdA(unsigned char cmdSend, long motorSpeed);
    void setCmdB(unsigned char cmdSend, long motorSpeed);
    char readDataA(unsigned char cmdSend,short* data);
    char readDataB(unsigned char cmdSend,short* data);
    char readPosA(unsigned char cmdSend, long* data);
    char readPosB(unsigned char cmdSend, long* data);
    void setDis(double dis);
    void setPos(double pos);
};