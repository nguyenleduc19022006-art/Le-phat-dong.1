#include "Motor.h"
Motor::Motor(int pinIN1, int pinIN2, int deadband, bool isReverse):
    _pinIN1(pinIN1), _pinIN2(pinIN2), _deadband(deadband), _isReverse(isReverse)
{}

void Motor::init(){
    pinMode(_pinIN1, OUTPUT);
    pinMode(_pinIN2, OUTPUT);
}

void Motor::coast(){
    _currentSpeed=0;
    analogWrite(_pinIN1, 0);
    analogWrite(_pinIN2, 0);
}
//phanh gap
void Motor::brake(){
    _currentSpeed=0;
    analogWrite(_pinIN1, 255);
    analogWrite(_pinIN2, 255);
}

void Motor::setspeed(int speed){
    if(_isReverse) speed=-speed;
    speed=constrain(speed, -255, 255);
    
    if(speed==0) {
        coast();
        return;
    }
    
    float control=speed/255.0f;
    //xung chua lam tron
    float unclippedPWM=control*(255.0f-_deadband)+copysign((float)_deadband, control);
    int processed_Speed=round(constrain(unclippedPWM, -255, 255));
    
    _currentSpeed=processed_Speed;
    if(processed_Speed>0){
        analogWrite(_pinIN1, processed_Speed);
        analogWrite(_pinIN2, 0);
    }
    else {
        analogWrite(_pinIN1, 0);
        analogWrite(_pinIN2, -processed_Speed);
    }
}

int Motor::getSpeed(){
    return _currentSpeed;
}

