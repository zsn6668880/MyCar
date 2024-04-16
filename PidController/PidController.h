#pragma once
#define A   100
#define B   300
#include <Arduino.h>
class PidController{
    private:
        double _kp;//比例系数
        double _ki;//积分系数
        double _kd;//微分系数
        double _integral;//积分值
        double _lastError;//上一次误差
        double _error;//当前误差
        double MAX_PWM;
        double MIN_PWM;
    public:
        PidController(double kp,double ki,double kd,double MAX,double MIN);
        PidController(double kp, double ki);
        PidController(double kp);
        PidController();
        void set_kp(double kp);
        void set_ki(double ki);
        void set_kd(double kd);
        double get_kp();
        double get_ki();
        double get_kd();
        double position_PID(double encoder,double target);
};

