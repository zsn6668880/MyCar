#include "Bistu_car.h"

double vx = 0;
double vy = 0;
double vz = 0;

using namespace Car;
    void Car::init(){
        Cmd::init();
        Cmd::setCmdA('R',0);
        Cmd::setCmdB('R', 0);
        delay(500);
        Cmd::setCmdA('U',0);
        Cmd::setCmdB('U', 0);
        setPIDFJ(20,5,0,40,0);
        // Cmd::setCmdA('F',10);
        // Cmd::setCmdB('F',10);
        // Cmd::setCmdA('f', 30);
        // Cmd::setCmdB('f', 30);
        // Cmd::setCmdA('P', 20);
        // Cmd::setCmdA('I', 5);
        // Cmd::setCmdA('D', 0);
        // Cmd::setCmdA('p', 20);
        // Cmd::setCmdA('i', 5);
        // Cmd::setCmdA('d', 3);

        // Cmd::setCmdB('P', 30);
        // Cmd::setCmdB('I', 8);
        // Cmd::setCmdB('D', 0);
        // Cmd::setCmdB('p', 30);
        // Cmd::setCmdB('i', 8);
        // Cmd::setCmdB('d', 0);
        
        // Cmd::setCmdA('F', 0);
        // Cmd::setCmdA('f', 0);
        // Cmd::setCmdB('F', 0);
        // Cmd::setCmdB('f', 0);

        // Cmd::setCmdA('J', 0);
        // Cmd::setCmdA('j', 0);
        // Cmd::setCmdB('J', 0);
        // Cmd::setCmdB('j', 0);
    }
    /*
       B \\----// C
         |      |
         |      |
       A //----\\ D
       w:31cm
       h:16cm
    */

    void Car::setSpeed(int vx,int vy,int vz){
        Cmd::setCmdB('m',-(vx + vy - vz*(Wheel_spacing+Wheel_axlespacing)));//A轮
        Cmd::setCmdB('M', (vx - vy - vz*(Wheel_spacing+Wheel_axlespacing)));//B轮
        Cmd::setCmdA('M', -(vx + vy + vz*(Wheel_spacing+Wheel_axlespacing)));//C轮
        Cmd::setCmdA('m', (vx - vy + vz*(Wheel_spacing+Wheel_axlespacing)));//D轮
    }

    void Car::getSpeed(){
        short va = 0;
        short vb = 0;
        short vc = 0;
        short vd = 0;
        Cmd::readDataA('S',&vc);
        Cmd::readDataA('s', &vd);
        Cmd::readDataB('s', &va);
        Cmd::readDataB('S', &vb);
        vx = (va + vd) / 2.0;
        vy = (va - vb) / 2.0;
        vz = (vc - va) / 2 * (Wheel_spacing + Wheel_axlespacing);
    }

    void Car::back(int speed){
        Cmd::setCmdA('M', -speed);//
        Cmd::setCmdA('m', speed);//
        Cmd::setCmdB('m', -speed);//
        Cmd::setCmdB('M', speed);//
    }

    void Car::setPIDFJ(int P, int I, int D, int F, int J){
        //A轮参数
        Cmd::setCmdA('P', P);
        Cmd::setCmdA('I', I);
        Cmd::setCmdA('D', D);
        Cmd::setCmdA('F', F);
        Cmd::setCmdA('J', J);

        //B轮参数
        Cmd::setCmdA('p', P);
        Cmd::setCmdA('i', I);
        Cmd::setCmdA('d', D);
        Cmd::setCmdA('f', F);
        Cmd::setCmdA('j', J);
        
        //C轮参数
        Cmd::setCmdB('p', P);
        Cmd::setCmdB('i', I);
        Cmd::setCmdB('d', D);
        Cmd::setCmdB('f', F);
        Cmd::setCmdB('j', J);

        //D轮参数
        Cmd::setCmdB('P', P);
        Cmd::setCmdB('I', I);
        Cmd::setCmdB('D', D);
        Cmd::setCmdB('F', F);
        Cmd::setCmdB('J', J);
    }

    void Car::setAccel(int accel){
        if(accel >= 0){
            Cmd::setCmdA('A', accel);
            Cmd::setCmdA('a', accel);
            Cmd::setCmdB('a', accel);
            Cmd::setCmdB('A', accel);
        }else{
            Cmd::setCmdA('C',-accel);
            Cmd::setCmdA('c', -accel);
            Cmd::setCmdB('c', -accel);
            Cmd::setCmdB('C', -accel);
        }
    }

    void Car::setMaxSpeed(int speed){
        if(speed < 0) speed *= -1;
        Cmd::setCmdA('B', speed);
        Cmd::setCmdA('b', speed);
        Cmd::setCmdB('b', speed);
        Cmd::setCmdB('B', speed);
    }

    void Car::setPos(int pos){
        Cmd::setCmdB('A',ACC);
        Cmd::setCmdB('B', MAXSPEED);
        Cmd::setCmdB('C', DEC);

        Cmd::setCmdA('A',ACC);
        Cmd::setCmdA('B', MAXSPEED);
        Cmd::setCmdA('C', DEC);

        Cmd::setCmdA('a',ACC);
        Cmd::setCmdA('b', MAXSPEED);
        Cmd::setCmdA('c', DEC);

        Cmd::setCmdB('a',ACC);
        Cmd::setCmdB('b', MAXSPEED);
        Cmd::setCmdB('c', DEC);

        Cmd::setCmdA('G', pos * LAP_A);
        Cmd::setCmdB('G', -pos * LAP_B);
        Cmd::setCmdA('g', -pos * LAP_A);
        Cmd::setCmdB('g', pos * LAP_B);
    }

    void Car::setDis(int dis){
        Cmd::setCmdB('A',0.5 * ACC);
        Cmd::setCmdB('B',0.5 * MAXSPEED);
        Cmd::setCmdB('C',0.5 * DEC);

        Cmd::setCmdA('A',0.5 * ACC);
        Cmd::setCmdA('B',0.5 * MAXSPEED);
        Cmd::setCmdA('C',0.5 * DEC);

        Cmd::setCmdB('a',0.5 * ACC);
        Cmd::setCmdB('b',0.5 * MAXSPEED);
        Cmd::setCmdB('c',0.5 * DEC);

        Cmd::setCmdA('a',0.5 * ACC);
        Cmd::setCmdA('b',0.5 * MAXSPEED);
        Cmd::setCmdA('c',0.5 * DEC);

        Cmd::setCmdA('E',dis * LAP_A);
        Cmd::setCmdA('e',-dis * LAP_A);
        Cmd::setCmdB('E',-dis * LAP_B);
        Cmd::setCmdB('e', dis * LAP_B);

    }

    void Car::left(int speed){
        Cmd::setCmdA('M', speed);//
        Cmd::setCmdA('m', speed);//
        Cmd::setCmdB('m', speed);//
        Cmd::setCmdB('M', speed);//
    }

    void Car::test(double pos){
        Cmd::setCmdB('A',0.5 * ACC);
        Cmd::setCmdB('B',0.5 * 0.9*MAXSPEED);
        Cmd::setCmdB('C',0.5 * DEC);

        Cmd::setCmdA('A',0.5 * ACC);
        Cmd::setCmdA('B',0.5 * MAXSPEED);
        Cmd::setCmdA('C',0.5 * DEC);

        Cmd::setCmdB('a',0.5 * ACC);
        Cmd::setCmdB('b',0.5 * 0.9*MAXSPEED);
        Cmd::setCmdB('c',0.5 * DEC);

        Cmd::setCmdA('a',0.5 * ACC);
        Cmd::setCmdA('b',0.5 * MAXSPEED);
        Cmd::setCmdA('c',0.5 * DEC);

        Cmd::setCmdA('E',-pos * LAP_A);
        Cmd::setCmdA('e', pos * LAP_A);
        Cmd::setCmdB('E',-pos * LAP_B);
        Cmd::setCmdB('e', pos * LAP_B);
    }

    void Car::isStop(bool* is){
        short* data1 = 0;
        short* data2 = 0;
        short* data3 = 0;
        short* data4 = 0;

        Cmd::readDataA('S',data1);
        Cmd::readDataB('S', data2);
        Cmd::readDataA('s', data3);
        Cmd::readDataB('s', data4);
        if(*data1 == 0 && *data2 == 0 && *data3 == 0 && *data4 == 0) *is = true;
        else *is = false;
    }