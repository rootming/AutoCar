#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "base.h"
#include "fan.h"

Fan::Fan(int speed, int range): proSpeed(speed),
                            proRange(range)
{
    setDeviceName("Coolers Fan");
    setDeviceType(MOTOR);
}

Fan::~Fan()
{
    softPwmStop(proSpeedPin);
}

void Fan::setPin(int speedPin)
{
    proSpeedPin = speedPin;
    softPwmCreate(speedPin, proSpeed, proRange);

}
