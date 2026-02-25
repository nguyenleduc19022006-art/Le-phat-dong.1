#include "UltrasonicSensor.h"



void UltrasonicSensor::init() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    
    digitalWrite(_trigPin, LOW);
}