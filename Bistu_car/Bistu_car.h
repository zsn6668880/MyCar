#pragma once
#include <CMD.h>
#define ACC 6000
#define DEC 6000
#define LAP_A 260000
#define LAP_B 260000
#define MAXSPEED 8000
#define Wheel_spacing 8//轴距
#define Wheel_axlespacing 15//轮距

extern double vx,vy, vz;

namespace Car{
    void test(double pos);
    void init();
    void setSpeed(int vx,int vy,int vz);
    void setPIDFJ(int P, int I, int D, int F, int J);
    void setAccel(int accel);
    void setMaxSpeed(int speed);
    void setDis(int dis);
    void setPos(int pos);
    void back(int speed);
    void left(int speed);
    void isStop(bool* is);
    void getSpeed();
};

