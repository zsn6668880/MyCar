#include "PidController.h"

    PidController::PidController(double kp, double ki, double kd,double MAX,double MIN):
    _kp(kp), _ki(ki), _kd(kd),MAX_PWM(MAX),MIN_PWM(MIN), _integral(0), _lastError(0), _error(0){};

    PidController::PidController(double kp, double ki):
    _kp(kp), _ki(ki), _kd(0), _integral(0), _lastError(0), _error(0){};

    PidController::PidController(double kp):
    _kp(kp), _ki(0), _kd(0), _integral(0), _lastError(0), _error(0){};

    PidController::PidController():
    _kp(0), _ki(0), _kd(0), _integral(0), _lastError(0), _error(0){};

    double PidController::position_PID(double encoder,double target){
        _error = encoder - target;
        _integral +=  _error;
        double pwm = _kp * _error + _ki * _integral + _kd * (_error - _lastError);
        if(pwm > MAX_PWM) pwm = MAX_PWM;
        if(pwm < MIN_PWM) pwm = MIN_PWM;
        return pwm;
    }

    void PidController::set_kp(double kp){
        _kp = kp;
    }

    void PidController::set_ki(double ki){
        _ki = ki;
    }

    void PidController::set_kd(double kd){
        _kd = kd;
    }

    double PidController::get_kp(){
        return _kp;
    }

    double PidController::get_ki(){
        return _ki;
    }

    double PidController::get_kd(){
        return _kd;
    }