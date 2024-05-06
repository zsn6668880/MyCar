#pragma once
#include <Arduino.h>
class myHCSR04 {
        private:
                int trigPin;
                int echoPin;
                
        public :
                double distance;
                myHCSR04(int trigPin,int echoPin);
                void init();
                double updateDistance();
                double upDis_Filter(int num);
};

