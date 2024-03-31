#include "MPU6050.h"

using namespace MPU6050;
float ypr[3] = { 0, 0, 0 };//NOTE - xyz[0]->Yaw(偏航角),xyz[1]->Pich（俯仰角）,xyz[2]->Roll（翻滚角）,以角度为单位

Simple_MPU6050 mpu;
void MPU6050::init(){
    mpu.begin();
    mpu.Set_DMP_Output_Rate_Hz(100);
    mpu.SetAddress(MPU6050_DEFAULT_ADDRESS);
    mpu.CalibrateMPU();
    mpu.load_DMP_Image();
    mpu.on_FIFO(updateData);
}

static void MPU6050::updateData(int16_t *gyro, int16_t *accel, int32_t *quat){
    updateYPR(quat);
}

void MPU6050::updateYPR(int32_t *quat){
    Quaternion q;
    VectorFloat gravity;
    float xyz[3] = { 0, 0, 0};
    mpu.GetQuaternion(&q,quat);
    mpu.GetGravity(&gravity,&q);
    mpu.GetYawPitchRoll(xyz,&q,&gravity);
    mpu.ConvertToDegrees(xyz,ypr);
}

void mustInLoop(){
    mpu.dmp_read_fifo(false);// Must be in loop  No Interrupt pin required at the expense of polling the i2c buss
}