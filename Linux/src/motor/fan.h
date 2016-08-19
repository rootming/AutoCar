#pragma once
#include "config.h"
#include "base.h"

class Fan: public Base, Device
{
public:
    explicit Fan(const Fan &) = delete;
    Fan &operator=(const Fan &) = delete;
    Fan(int speed = 100, int range = 255);
    void setPin(int speedPin);
    ~Fan();

private:
    int proSpeedPin;
    int proSpeed;
    int proRange;
};
