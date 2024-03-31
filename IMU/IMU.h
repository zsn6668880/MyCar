#pragma once
#include <Arduino.h>
#include "wit_c_sdk.h"
#include "REG.h"
#define IMU_Serial Serial1

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80

namespace imu{
    extern const uint32_t c_uiBaud[10];
    void init();
    void update();
    void CopeCmdData(unsigned char ucData);
    float* getAngle();
    float* getAcc();
    float* getGyro();
    static void CmdProcess(void);
    static bool AutoScanSensor(void);
    static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
    static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
    static void Delayms(uint16_t ucMs);
    static void ShowHelp(void);



};