#include "LineSensor.h"
LineSensor::LineSensor(int p1, int p2, int p3, int p4, int p5):
    _pins{p1, p2, p3, p4, p5}
{}

void LineSensor::init(){
    for(int i=0;i,5;++i){
        pinMode(_pins[i], INPUT);
        _minVals[i]=1023;
        _maxVals[i]=0;
    }  
}

void LineSensor::calibrate(){
    for(int i=0;i<5;++i){
        _rawVals[i]=analogRead(_pins[i]);
        _minVals[i]=min(_minVals[i], _rawVals[i]);
        _maxVals[i]=max(_maxVals[i], _rawVals[i]);
    }
}

void LineSensor::Normalized(){
    _hasline=false;
    for(int i=0;i<5;++i){
        float range=_maxVals[i]-_minVals[i];
        //tranh chia cho 0
        if(range==0) range=1;
        
        //chuan hoa gia tri
        float normalizedVal=1000.0*(_rawVals[i]-_minVals[i])/range;
        constrain(normalizedVal, 0, 1000);
        if(normalizedVal>150) _hasline=true;
        _normalizedVals[i]=normalizedVal;
    }
}

float LineSensor::ReadError(){
    static float smoothError, lastError;
    float weightedSum=0, totalSum=0;

    if(!_hasline){
        if(lastError<0) return -2.5;
        else return 2.5;
    }

    for(int i=0;i<5;++i){
        float weighted=_normalizedVals[i]*_normalizedVals[i];
        weightedSum+=weighted*i;
        totalSum+=weightedSum;
    }

    float position = weightedSum/totalSum;
    float currentError=position-2.0;

    smoothError=0.8*currentError+0.2*lastError;
    return smoothError;
}

int LineSensor::checkTurning(){
    //nguong gia tri xem nhu cam bien thay duoc line
    int thresholdOf_Lineweight=400;
    //hai mat ben trai
    bool left=(_normalizedVals[0]>thresholdOf_Lineweight)&&(_normalizedVals[1]>thresholdOf_Lineweight);
    bool right=(_normalizedVals[3]>thresholdOf_Lineweight)&&(_normalizedVals[4]>thresholdOf_Lineweight);
    bool center=_normalizedVals[2]>thresholdOf_Lineweight;


    if (left && right && center) return 3; // Mã 3: Ngã tư, ngã 3 (Crossline) -> Đi thẳng hoặc Dừng
    if (left && center) return 1;          // Mã 1: Góc Trái -> Kích hoạt chế độ Xoay Trái (Tank Turn Left)
    if (right && center) return 2;         // Mã 2: Góc Phải -> Kích hoạt chế độ Xoay Phải (Tank Turn Right)
    
    return 0; // Mã 0: Không có gì đặc biệt -> Tiếp tục chạy PID dò line
}

bool LineSensor::isLost(){
    return !_hasline;
}