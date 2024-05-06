#include "myHCSR04.h"

myHCSR04::myHCSR04(int tp, int ep) {
    trigPin = tp;
    echoPin = ep;
    distance = 0;
}

void myHCSR04::init() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double myHCSR04::updateDistance() {
    //发送超声波脉冲
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    auto temp = pulseIn(echoPin, HIGH,30000);
    this->distance = temp * 0.034 / 2;
    return this->distance;
   
}

double myHCSR04::upDis_Filter(int num){
    double disArray[num];
    for(int i = 0; i < num; i++){
       disArray[i] = updateDistance();
    }

    for(int i = 0; i < num; i++){
        for(int j = i + 1; j < num; j++){
            if(disArray[i] > disArray[j]){
                double temp = disArray[i];
                disArray[i] = disArray[j];
                disArray[j] = temp;
            }
        }
    }

    return this->distance = disArray[(num - 1) / 2];

}





