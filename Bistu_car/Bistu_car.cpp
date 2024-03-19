#include "Bistu_car.h"

using namespace Car;
    void Car::init(){
        Cmd::init();
        Cmd::setCmdA('R',0);
        Cmd::setCmdB('R', 0);
        delay(500);
        Cmd::setCmdA('U',0);
        Cmd::setCmdB('U', 0);
        setPIDFJ(20,5,0,30,0);
        
    }

    void Car::setSpeed(int speed){
        Cmd::setCmdA('M',-speed);//A轮
        Cmd::setCmdA('m',speed);//B轮
        Cmd::setCmdB('m', -speed);//C轮
        Cmd::setCmdB('M', speed);//D轮
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

    void Car::setDis(int dis){
        Cmd::setCmdA('E',dis);
    }

    void Car::setPos(int pos){
        Cmd::setCmdB('A',1000);
        Cmd::setCmdB('B', 3000);
        Cmd::setCmdB('C', 1000);

        Cmd::setCmdA('A',1000);
        Cmd::setCmdA('B', 3000);
        Cmd::setCmdA('C', 1000);

        Cmd::setCmdA('a',1000);
        Cmd::setCmdA('b', 3000);
        Cmd::setCmdA('c', 1000);

        Cmd::setCmdB('a',1000);
        Cmd::setCmdB('b', 3000);
        Cmd::setCmdB('c', 1000);

        Cmd::setCmdA('G', pos * LAP);
        Cmd::setCmdB('G', -pos * LAP);
        Cmd::setCmdA('g', -pos * LAP);
        Cmd::setCmdB('g', pos * LAP);
    }

    void Car::test(){
        // Cmd::setCmdB('A',1000);
        // Cmd::setCmdB('B', 3000);
        // Cmd::setCmdB('C', 1000);
        // Cmd::setCmdB('G',-10000000);

        // Cmd::setCmdA('A',1000);
        // Cmd::setCmdA('B', 3000);
        // Cmd::setCmdA('C', 1000);
        // Cmd::setCmdA('G', LAP);

        // Cmd::setCmdA('a',1000);
        // Cmd::setCmdA('b', 3000);
        // Cmd::setCmdA('c', 1000);
        // Cmd::setCmdA('g', LAP);

        // Cmd::setCmdB('a',1000);
        // Cmd::setCmdB('b', 3000);
        // Cmd::setCmdB('c', 1000);
        // Cmd::setCmdB('g', LAP);


    }