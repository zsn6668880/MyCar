#pragma once
#include <Arduino.h>


class Sharp{
    private:
        int _pin;
    public:
        Sharp(int pin);
        void init();
        double updateDistance();
};