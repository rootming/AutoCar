#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "../config/config.h"
#include "brightness.h"

Brightness::Brightness()
{
   setAddr(_ADC_BG_ADDRESS);
}

int Brightness::getValue(void)
{
    return analogRead(_ADC_BASE_PIN + _ADC_BG_ADDRESS);
}