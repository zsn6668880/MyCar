#pragma once
#include <CMD.h>
#define LAP 260000
namespace Car{
    void test();
    void init();
    void setSpeed(int speed);
    void setPIDFJ(int P, int I, int D, int F, int J);
    void setAccel(int accel);
    void setMaxSpeed(int speed);
    void setDis(int dis);
    void setPos(int pos);
};

