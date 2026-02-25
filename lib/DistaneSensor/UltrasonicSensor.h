#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H 

#include<Arduino.h>

class UltrasonicSensor{
private:
    int _trigPin;
    int _echoPin;

    //he so loc nhieu
    float _alpha;
    float _smoothedDistance;
    unsigned long _maxTimeout; // Thời gian chờ tối đa (Chống treo)

public: 
    /**
     * @param trigPin Chân phát sóng
     * @param echoPin Chân nhận sóng
     */
    UltrasonicSensor(int trigPin, int echoPin, float alpha = 0.4);
    void init();

    /**
     * @return Khoảng cách (cm). Nếu vượt quá tầm đo, trả về -1.0
     */    
    float readDistance();

    //lay ket qua khoang cach do duoc
    float getDistance();
};
#endif