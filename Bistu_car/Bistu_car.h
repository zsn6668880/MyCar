#pragma once
#include <CMD.h>
#define ACC 6000
#define DEC 6000
#define LAP_A 260000
#define LAP_B 260000
#define MAXSPEED 20000
#define Wheel_spacing 2.75//轴距
#define Wheel_axlespacing 15//轮距
#define Wheel_R 5

namespace Car{
    void test(double pos);
    void init();
    void setSpeed(int vx,int vy,int vz);
    void setPIDFJ(int P, int I, int D, int F, int J);
    void setAccel(int accel);
    void setMaxSpeed(int speed);
    void setDis(int dis);
    void setPos(int pos);
    void setSpeed_four_wheel(double vx,double vz);
};

