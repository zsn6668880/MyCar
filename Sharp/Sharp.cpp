#include <Sharp.h>


Sharp::Sharp(int pin) {
  _pin = pin;
}

void Sharp::init(){
    pinMode(_pin, INPUT);
} 

double Sharp::updateDistance(){
    float volts = analogRead(_pin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S 
    return distance;
}