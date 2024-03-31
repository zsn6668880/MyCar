#include "IMU.h"
using namespace imu;

static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
const uint32_t imu::c_uiBaud[10] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
float fAcc[3], fGyro[3], fAngle[3];
int i;
float fAngle_tmp = 0;

//NOTE - 帮助文档
// Help document(帮助文档)
// ************************	 WIT_SDK_DEMO	************************
// ************************          HELP           ************************
// UART SEND:a   Acceleration calibration.
// UART SEND:m   Magnetic field calibration,After calibration send:   e\\r\\n   to indicate the end
// UART SEND:U   Bandwidth increase.
// UART SEND:u   Bandwidth reduction.
// UART SEND:B   Baud rate increased to 115200.
// UART SEND:b   Baud rate reduction to 9600.
// UART SEND:R   The return rate increases to 10Hz.
// UART SEND:r   The return rate reduction to 1Hz.
// UART SEND:C   Basic return content: acceleration, angular velocity, angle, magnetic field.
// UART SEND:c   Return content: acceleration.
// UART SEND:h   help.
// ******************************************************************************

//REVIEW - 帮助文档
static void imu::ShowHelp(void){
    Serial.println("******************************");
  Serial.println("Please see the help document");
	Serial.println("******************************");
}

//NOTE - 处理命令
static void imu::CmdProcess(void)
{
	switch(s_cCmd)
	{
		case 'a':	
			if(WitStartAccCali() != WIT_HAL_OK) 
				Serial.println("Set AccCali Error");
			break;
		case 'm':	
			if(WitStartMagCali() != WIT_HAL_OK) 
				Serial.println("Set MagCali Error");
			break;
		case 'e':	
			if(WitStopMagCali() != WIT_HAL_OK)
				Serial.println("Set MagCali Error");
			break;
		case 'u':	
			if(WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK) 
				Serial.println("Set Bandwidth Error");
			break;
		case 'U':	
			if(WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK) 
				Serial.println("Set Bandwidth Error");
			break;
		case 'B':	
			if(WitSetUartBaud(WIT_BAUD_115200) != WIT_HAL_OK) 
				Serial.println("Set Baud Error");
			else 
				IMU_Serial.begin(115200);											
			break;
		case 'b':	
			if(WitSetUartBaud(WIT_BAUD_9600) != WIT_HAL_OK)
				Serial.println("Set Baud Error");
			else 
				IMU_Serial.begin(9600);												
			break;
		case 'R':	
			if(WitSetOutputRate(RRATE_10HZ) != WIT_HAL_OK) 
				Serial.println("Set Rate Error");
			break;
		case 'r':	
			if(WitSetOutputRate(RRATE_1HZ) != WIT_HAL_OK) 
				Serial.println("Set Rate Error");
			break;
		case 'C':	
			if(WitSetContent(RSW_ACC|RSW_GYRO|RSW_ANGLE|RSW_MAG) != WIT_HAL_OK) 
				Serial.println("Set RSW Error");
			break;
		case 'c':	
			if(WitSetContent(RSW_ACC) != WIT_HAL_OK) 
				Serial.println("Set RSW Error");
			break;
		case 'h':
			ShowHelp();
			break;
	}
	s_cCmd = 0xff;
}

//REVIEW - 发送数据到传感器
static void imu::SensorUartSend(uint8_t *p_data, uint32_t uiSize)
{
  for(int i = 0; i < uiSize ; i++)
  {
    IMU_Serial.write(*(p_data+i)); 
  }
}

//REVIEW - 延时函数
static void imu::Delayms(uint16_t ucMs)
{
    //TODO - 如果要用FreeRTOS的话不能使用delay函数，要使用vTaskDelay函数
	delay(ucMs);
}

//REVIEW - 更新传感器数据
static void imu::SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
	int i;
    for(i = 0; i < uiRegNum; i++)
    {
        switch(uiReg)
        {
//            case AX:
//            case AY:
            case AZ:
				s_cDataUpdate |= ACC_UPDATE;
            break;
//            case GX:
//            case GY:
            case GZ:
				s_cDataUpdate |= GYRO_UPDATE;
            break;
//            case HX:
//            case HY:
            case HZ:
				s_cDataUpdate |= MAG_UPDATE;
            break;
//            case Roll:
//            case Pitch:
            case Yaw:
				s_cDataUpdate |= ANGLE_UPDATE;
            break;
            default:
				s_cDataUpdate |= READ_UPDATE;
			break;
        }
		uiReg++;
    }
}

//REVIEW - 自动扫描传感器
static bool imu::AutoScanSensor(void)
{
  static bool rt = false;
  if(rt)
    return true;

	static int i = 0, step = 0;
  switch(step)
  {
    case 0:
      IMU_Serial.begin(c_uiBaud[i]);
      step++;
      break;
    case 1:
      s_cDataUpdate = 0;
      WitReadReg(AX, 3);
      delay(100);
      step++;
      break;
    case 2:
      if(s_cDataUpdate != 0)
			{
        Serial.print(c_uiBaud[i]);
				Serial.println(" baud find sensor");
				ShowHelp();
				rt = true;
			}else{
        WitReadReg(AX, 3);
        delay(100);
        step++;
      }
      break;
    case 3:
      i++;
      if(i >= 10)
      {
        Serial.println("can not find sensor");
	      Serial.println("please check your connection");
        i = 0;
        delay(1000);
      }
      step = 0;
      break;
    default:
      i = 0;
      step = 0;
      break;
  }

  return rt;
	
}

//REVIEW - 处理接收到的命令数据
void imu::CopeCmdData(unsigned char ucData)
{
	static unsigned char s_ucData[50], s_ucRxCnt = 0;
	
	s_ucData[s_ucRxCnt++] = ucData;
	if(s_ucRxCnt<3)return;										//Less than three data returned
	if(s_ucRxCnt >= 50) s_ucRxCnt = 0;
	if(s_ucRxCnt >= 3)
	{
		if((s_ucData[1] == '\r') && (s_ucData[2] == '\n'))
		{
			s_cCmd = s_ucData[0];
			memset(s_ucData,0,50);//
			s_ucRxCnt = 0;
		}
		else 
		{
			s_ucData[0] = s_ucData[1];
			s_ucData[1] = s_ucData[2];
			s_ucRxCnt = 2;
			
		}
	}

}

//REVIEW - 初始化
void imu::init(){
    IMU_Serial.begin(115200);
    Serial.begin(115200);
    WitInit(WIT_PROTOCOL_NORMAL, 0x50);
    WitSerialWriteRegister(SensorUartSend);
    WitRegisterCallBack(SensorDataUpdata);
    WitDelayMsRegister(Delayms);
    // Serial.println("welcome to use!");
    CopeCmdData('R');
    CopeCmdData('a');
    // CopeCmdData('C');
}

//REVIEW - 更新数据
void imu::update(){
    //接收
  uint32_t len = IMU_Serial.available();
  while(len--)
  {
    WitSerialDataIn((char)IMU_Serial.read());
  }
  if(AutoScanSensor())
  {
    //解析
    CmdProcess();
    if(s_cDataUpdate)
    {
      for(i = 0; i < 3; i++)
      {
        fAcc[i] = sReg[AX+i] / 32768.0f * 16.0f;
        fGyro[i] = sReg[GX+i] / 32768.0f * 2000.0f;
      }
      if(sReg[TEMP] - sReg[Roll] > 10 | sReg[Roll] - sReg[TEMP] > 10)
      {
        fAngle[0] = sReg[Roll] / 32768.0f * 180.0f;
        fAngle_tmp = fAngle[0];
      }
      else   fAngle[0] = fAngle_tmp;
      
      for(i = 1; i<3;i++)
      {
        fAngle[i] = sReg[Roll+i] / 32768.0f * 180.0f;
      }

    //   if(s_cDataUpdate & ACC_UPDATE)
    //   {
    //     Serial.print("acc: ");
    //     Serial.print(fAcc[0]);
    //     Serial.print(" ");
    //     Serial.print(fAcc[1]);
    //     Serial.print(" ");
    //     Serial.println(fAcc[2]);
    //     s_cDataUpdate &= ~ACC_UPDATE;
    //   }
    //   if(s_cDataUpdate & GYRO_UPDATE)
    //   {
    //     Serial.print("gyro: ");
    //     Serial.print(fGyro[0]);
    //     Serial.print(" ");
    //     Serial.print(fGyro[1]);
    //     Serial.print(" ");
    //     Serial.println(fGyro[2]);
    //     s_cDataUpdate &= ~GYRO_UPDATE;
    //   }
    //   if(s_cDataUpdate & ANGLE_UPDATE)
    //   {
    //     Serial.print("angle: ");
    //     Serial.print(fAngle[0]);
    //     Serial.print(" ");
    //     Serial.print(fAngle[1]);
    //     Serial.print(" ");
    //     Serial.println(fAngle[2]);
    //     s_cDataUpdate &= ~ANGLE_UPDATE;
    //   }
    //   if(s_cDataUpdate & MAG_UPDATE)
    //   {
    //     Serial.print("mag: ");
    //     Serial.print(sReg[HX]);
    //     Serial.print(" ");
    //     Serial.print(sReg[HY]);
    //     Serial.print(" ");
    //     Serial.println(sReg[HZ]);
    //     s_cDataUpdate &= ~MAG_UPDATE;
    //   }
    //   delay(500);
    }
  }
}

float* imu::getAngle(){
    return fAngle;
}

float* imu::getAcc(){
    return fAcc;
}

float* imu::getGyro(){
    return fGyro;
}