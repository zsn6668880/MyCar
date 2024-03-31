#pragma once 
#include <Simple_MPU6050.h>
#define MPU6050_ADDRESS_AD0_LOW 0x68 //address pin low(GND)
#define MPU6050_ADDRESS_AD0_HIGH 0x69 //address pin high(VCC)
#define MPU6050_DEFAULT_ADDRESS MPU6050_ADDRESS_AD0_LOW
#define spamtimer(t) for (static uint32_t SpamTimer; (uint32_t)(millis() - SpamTimer) >= (t); SpamTimer = millis()) // (BLACK BOX) Ya, don't complain that I used "for(;;){}" instead of "if(){}" for my Blink Without Delay Timer macro. It works nicely!!!
/* printfloatx() is a helper Macro used with the Serial class to simplify my code and provide enhanced viewing of Float and interger values:
   usage: printfloatx(Name,Variable,Spaces,Precision,EndTxt);
   Name and EndTxt are just char arrays
   Variable is any numerical value byte, int, long and float
   Spaces is the number of spaces the floating point number could possibly take up including +- and decimal point.
   Precision is the number of digits after the decimal point set to zero for intergers
*/
#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) print(Name); {char S[(Spaces + Precision + 3)];Serial.print(F(" ")); Serial.print(dtostrf((float)Variable,Spaces,Precision ,S));}Serial.print(EndTxt);//Name,Variable,Spaces,Precision,EndTxt

extern Simple_MPU6050 mpu;
extern float ypr[3];

namespace MPU6050{
    
    void init();
    static void updateData(int16_t *gyro, int16_t *accel, int32_t *quat);
    void updateYPR(int32_t *quat);
    float* getYPR();
    void mustInLoop();
}