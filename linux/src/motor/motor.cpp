#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

#include "base.h"
#include "motor.h"

using namespace std;

Motor::Motor(int speed, int range): proLeftSpeed(speed), proRightSpeed(speed), proRange(range)
{
    if(base == nullptr){
        cerr << "Now init GPIO" << endl;
        initGPIO();
    }
    setPin();
}

Motor::~Motor()
{
    softPwmStop(proLeftPin);
    softPwmStop(proRightPin);
}

void Motor::setPin(int left, int right, int INT0, int INT1, int INT2, int INT3)
{

    softPwmStop(proLeftPin);
    softPwmStop(proRightPin);

    softPwmCreate(proLeftPin, proLeftSpeed, proRange);
    softPwmCreate(proRightPin, proRightSpeed, proRange);
    pinMode(proINT0, OUTPUT);
    pinMode(proINT1, OUTPUT);
    pinMode(proINT2, OUTPUT);
    pinMode(proINT3, OUTPUT);
}

void Motor::setLeftSpeed(int speed)
{
    if(speed > 0){
        digtalWrite(proINT0, HIGH);
        digtalWrite(proINT1, LOW);

    }
    else if(speed == 0){
        digtalWrite(proINT0, LOW);
        digtalWrite(proINT1, LOW);

    }
    else{
        digtalWrite(proINT0, LOW);
        digtalWrite(proINT1, HIGH);
    }
    softPwmWrite(proLeftPin, abs(speed));
    proLeftSpeed = speed;
}

void Motor::setRightSpeed(int speed)
{
    if(speed > 0){
        digtalWrite(proINT2, HIGH);
        digtalWrite(proINT3, LOW);

    }
    else if(speed == 0){
        digtalWrite(proINT2, LOW);
        digtalWrite(proINT3, LOW);

    }
    else{
        digtalWrite(proINT2, LOW);
        digtalWrite(proINT3, HIGH);
    }
    softPwmWrite(proRightPin, abs(speed));
    proRightSpeed = speed;
}



