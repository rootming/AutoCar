#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "config.h"
#include "temperature.h"

Temperature::Temperature()
{
    setDeviceName("Temperature Sensor");
    setDeviceType(SENSOR);
    setAddr(ADC_BG_ADDRESS);
}

int Temperature::getValue(void)
{
    return analogRead(ADC_BASE_PIN + ADC_DIO_ADDRESS);
}
