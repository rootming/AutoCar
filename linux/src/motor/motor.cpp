#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "base.h"
#include "motor.h"

using namespace std;

Motor::Motor(int speed, int range): proLeftSpeed(speed), proRightSpeed(speed), proRange(range)
{
    
}

Motor::~Motor()
{
    softPwmStop(proLeftPin);
    softPwmStop(proRightPin);
    digitalWrite(proINT0, LOW);
    digitalWrite(proINT1, LOW);
    digitalWrite(proINT2, LOW);
    digitalWrite(proINT3, LOW);


}

void Motor::setPin(int left, int right, int INT0, int INT1, int INT2, int INT3)
{
    inited = true;
//    softPwmStop(proLeftPin);
//    softPwmStop(proRightPin);
    proLeftPin = left;
    proRightPin = right;
    proINT0 = INT0; 
    proINT1 = INT1; 
    proINT2 = INT2; 
    proINT3 = INT3; 

    softPwmCreate(proLeftPin, proLeftSpeed, proRange);
    softPwmCreate(proRightPin, proRightSpeed, proRange);

    pinMode(proINT0, OUTPUT);
    pinMode(proINT1, OUTPUT);
    pinMode(proINT2, OUTPUT);
    pinMode(proINT3, OUTPUT);

    digitalWrite(proINT0, LOW);
    digitalWrite(proINT1, LOW);
    digitalWrite(proINT2, LOW);
    digitalWrite(proINT3, LOW);

    
}

void Motor::setLeftSpeed(int speed)
{
    if(!isInit()){
        cerr << "Need set PIN." << endl;
        return;
    }
    if(speed > 0){
        digitalWrite(proINT0, HIGH);
        digitalWrite(proINT1, LOW);

    }
    else if(speed == 0){
        digitalWrite(proINT0, LOW);
        digitalWrite(proINT1, LOW);

    }
    else{
        digitalWrite(proINT0, LOW);
        digitalWrite(proINT1, HIGH);
    }
    softPwmWrite(proLeftPin, abs(speed));
    proLeftSpeed = speed;
}

void Motor::setRightSpeed(int speed)
{
    if(!isInit()){
        cerr << "Need set PIN." << endl;
        return;
    }
    if(speed > 0){
        digitalWrite(proINT2, HIGH);
        digitalWrite(proINT3, LOW);

    }
    else if(speed == 0){
        digitalWrite(proINT2, LOW);
        digitalWrite(proINT3, LOW);

    }
    else{
        digitalWrite(proINT2, LOW);
        digitalWrite(proINT3, HIGH);
    }
    softPwmWrite(proRightPin, abs(speed));
    proRightSpeed = speed;
}



