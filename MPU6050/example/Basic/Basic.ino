#include "MPU6050.h"

//用了Simp_MPU6050这个库，记着安装这个库
void setup(){
    Serial.begin(9600);
    MPU6050::init();
}

void loop(){
    mpu.dmp_read_fifo(false);//这行代码必须写在loop里面
    Serial.print("Yaw:");
    Serial.print((int)ypr[0]);//ypr[3]数组定义在MPU6050.cpp文件里面，ypr[0]->偏航角,ypr[1]->俯仰角,ypr[2]->翻滚角
    //FIXME - Yaw的值能用，Pitch和Roll的值不确定是硬件问题还是软件问题，先别用！
    Serial.print("\tPitch:");
    Serial.print((int)ypr[1]);
    Serial.print("\tRoll:");
    Serial.println((int)ypr[2]);
}