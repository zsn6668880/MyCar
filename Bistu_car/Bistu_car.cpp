#include "Bistu_car.h"



using namespace Car;
    void Car::init(){
        Cmd::init();
        Cmd::setCmdA('R',0);
        Cmd::setCmdB('R', 0);
        delay(500);
        Cmd::setCmdA('U',0);
        Cmd::setCmdB('U', 0);
        setPIDFJ(20,0,0,30,0);
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
        int va = -(vx + vy - vz*(Wheel_spacing+Wheel_axlespacing));
        int vb = (vx - vy - vz*(Wheel_spacing+Wheel_axlespacing));
        int vc = -(vx + vy + vz*(Wheel_spacing+Wheel_axlespacing));
        int vd = (vx - vy + vz*(Wheel_spacing+Wheel_axlespacing));

        Cmd::setCmdB('m',va);//A轮
        Cmd::setCmdB('M',vb);//B轮
        Cmd::setCmdA('M',vc);//C轮
        Cmd::setCmdA('m',vd);//D轮
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

    void Car::test(double pos){
        Cmd::setCmdB('M',0);
        Cmd::setCmdB('m',0);
        Cmd::setCmdB('A', ACC);
        Cmd::setCmdB('B', MAXSPEED / 1.5);
        Cmd::setCmdB('C', DEC);

        Cmd::setCmdA('A', ACC);
        Cmd::setCmdA('B', MAXSPEED / 1.5);
        Cmd::setCmdA('C', DEC);

        Cmd::setCmdB('a', ACC);
        Cmd::setCmdB('b', MAXSPEED / 1.5);
        Cmd::setCmdB('c', DEC);

        Cmd::setCmdA('a', ACC);
        Cmd::setCmdA('b', MAXSPEED / 1.5);
        Cmd::setCmdA('c', DEC);

        Cmd::setCmdA('E',-pos * LAP_A);
        Cmd::setCmdA('e', pos * LAP_A);
        Cmd::setCmdB('E',-pos * LAP_B);
        Cmd::setCmdB('e', pos * LAP_B);
    }