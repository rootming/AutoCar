#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "config.h"
#include "brightness.h"

Brightness::Brightness()
{
    setDeviceName("Brightness Sensor");
    setDeviceType(SENSOR);
    setAddr(ADC_BG_ADDRESS);
}

int Brightness::getValue()
{
    return analogRead(ADC_BASE_PIN + ADC_BG_ADDRESS);
}
