#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "config.h"
#include "brightness.h"

Brightness::Brightness()
{
   setAddr(ADC_BG_ADDRESS);
   setDeviceName("Brightness Sensor");
   setDeviceType(SENSOR);

}

int Brightness::getValue(void)
{
    return analogRead(ADC_BASE_PIN + ADC_BG_ADDRESS);
}
