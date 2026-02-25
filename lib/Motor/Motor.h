#ifndef MOTOR_H
#define MOTOR_H

#include<Arduino.h>

class Motor{
private: 
    int _pinIN1, _pinIN2;
    int _currentSpeed, _deadband;
    bool _isReverse;
public: 
    Motor(int pinIN1, int pinIN2, int deadband, bool isReverse=false);
    void init();
    void setspeed(int speed);
    void coast();
    void brake();
    int getSpeed();
    void setDeadband(int Deadband);
};  
#endif