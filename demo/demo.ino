#include <Bistu_car.h>
#include <IMU.h>
#include <Sharp.h>
#include <myHCSR04.h>
#include <PidController.h>
#include <MsTimer2.h>
// #include <HuskylensController.h>
// #include <SoftwareSerial.h>
#define NUM 13


myHCSR04 hlf(23, 22);
myHCSR04 hrf(21, 20);
myHCSR04 hlb(25,24);
myHCSR04 hrb(26,27);
PidController pid(250,0,0,5000,-5000);
PidController pid_imu(8,0,0,60,-60);
PidController pid2(200, 0, 0, 3000, 3000);
PidController pid_init(25,0,0,80,-80);
PidController pid_sharp(10,0,0,80,-80);

Sharp sl(A14);
Sharp sr(A15);

double vx = 0, vy = 0, vz = 0;
float* ang;
float* acc;
double imuTarget = 0;

int flag = 1;

void isr_timer2(){
  double dis = sr.updateDistance();
  if(dis < 70 && ang[1] < -5){

   vz = pid_sharp.position_PID(abs(dis - 58) < 1 ? 58 : dis, 58); 
    // Car::setSpeed(abs(20 * vz), 0, -vz);
    Car::setSpeed(1000,0,-vz);
    
  }
}

int _imu_is_target(){
  return ang[2] - imuTarget >= 0 ? 1 : -1;
}


void setup(){
  imu::init();
  Car::init();
  hlf.init();
  hrf.init();
  hlb.init();
  hrb.init();
  sl.init();
  sr.init();
  ang = imu::getAngle();
  MsTimer2::set(300,isr_timer2);
 


  // task1
  int count_task1 = 0;
  while(true){
    imu::update();
    Serial.println("task1 begin");
    hrb.upDis_Filter(NUM);
    hlb.upDis_Filter(NUM);
    
    double dis = hlb.distance - hrb.distance;
    float target = -0.50;
    vz = pid_init.position_PID(abs(dis - target) > 0.20 ? dis : target,target);
    Car::setSpeed(0,0,vz);

    if(vz == 0) ++count_task1;
    if(count_task1 > 30){
      imuTarget = ang[2];
      break;
    }
  }

  //task2
  int count_task2 = 0;
  while(true){
    imu::update();
    Serial.println("task2 begin");
    hlf.updateDistance();
    vx = pid.position_PID((int)(hlf.distance),22);
    vz = pid_imu.position_PID(ang[2],imuTarget);
    Car::setSpeed(vx,0,-vz);
    if(vx == 0) count_task2++;
    if(count_task2 > 15){
      imuTarget += 90;
      if(imuTarget > 180) imuTarget -= 360;
      if(imuTarget < -180) imuTarget += 360;
      break;
    }
  }
 

  Car::test(0.78);
  delay(2000);

  //  count_task1 = 0;
  //  while(true){
  //   Serial.println("task1 begin");
  //   hrb.updateDistance();
  //   hlb.updateDistance();
  //   imu::update();
  //   vz = pid_init.position_PID((int)(hlb.distance - hrb.distance),0);
  //   Car::setSpeed(0,0,vz);

  //   if(vz == 0) ++count_task1;
  //   if(count_task1 > 30){
  //     imuTarget = ang[2];
  //     break;
  //   }
  // }

  // int count_task3 = 0;
  // while(true){
  //   imu::update();
  //   hlb.updateDistance();
  //   hrb.updateDistance();

  //   vz = pid_init.position_PID((int)(hlb.distance - hrb.distance),0);
  //   Car::setSpeed(0, 0, vz);

  //   if(vz == 0) count_task3++;
  //   if(count_task3 > 30){
  //     imuTarget = ang[2];
  //     break;
  //   }
    
  // }
 

  // MsTimer2::start();

  // while(true){
  //   imu::update();
  //   Serial.print("imuTarget:");
  //   Serial.println(imuTarget);
  //   Serial.print("ang:");
  //   Serial.println(ang[2]);
  // }
  
  while(true){
    imu::update();
    vz = pid_imu.position_PID(abs(ang[2] - imuTarget) < 0.8 ? imuTarget : ang[2], imuTarget);
    Car::setSpeed(5000,0,-vz);

    Serial.println(ang[1]);
    if(ang[1] > 1 && ang[1] < 6){
      break;
    }
    
  }


  // MsTimer2::stop();
  count_task1 = 0;
  while(true){
    imu::update();
    hlf.updateDistance();
    vx = pid.position_PID((int)(hlf.distance), 10);
    vz = pid_imu.position_PID(ang[2], imuTarget);
    Car::setSpeed(vx, 0, 0);
    if(vx == 0) count_task1++;
    if(count_task1 > 15) break;
  }

  Car::test(0.78);
  delay(2000);

  int count = 0;
  while(true){
    hrb.updateDistance();
    hlb.updateDistance();
    imu::update();
    vz = pid_init.position_PID((int)(hlb.distance - hrb.distance),0);
    Car::setSpeed(0, 0, vz);

    if(vz == 0) count++;
    if(count == 30){
      delay(2000);
      imuTarget = ang[2];
      break;
    }
  }

  count = 0;
  while(true){
    imu::update();
    hlf.updateDistance();
    vz = pid_imu.position_PID(ang[2],imuTarget);
    vx = pid.position_PID((int)(hlf.distance), 8);
    Car::setSpeed(vx, 0, -vz);
    if(vx == 0) count++;
    if(count > 30){
      break;
    }
  }

  // count = 0;
  // while(true){
  //   hrf.updateDistance();
  //   hlf.updateDistance();

  //   vz = pid_init.position_PID((int)(hlf.distance - hrf.distance), 0);
  //   Car::setSpeed(0, 0, -vz);

  //   if(vz == 0) count++;
  //   if(count > 30){
  //     imuTarget = ang[2];
  //     break;
  //   }
  // }

  Car::test(0.78);

}

void loop(){
}