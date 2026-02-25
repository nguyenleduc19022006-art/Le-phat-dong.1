#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include<Arduino.h>

class LineSensor{
private:
    int _pins[5], _minVals[5], _maxVals[5]; 
    int _rawVals[5];
    float _normalizedVals[5];
    bool _hasline;
public:
    LineSensor(int p1, int p2, int p3, int p4, int p5);
    void init();
    void calibrate();
    void Normalized();
    float ReadError();
    int checkTurning();
    bool isLost();
};

#endif