#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "config.h"
#include "temperature.h"

Temperature::Temperature()
{
   setAddr(_ADC_BG_ADDRESS);
}

int Temperature::getValue(void)
{
    return analogRead(_ADC_BASE_PIN + _ADC_DIO_ADDRESS);
}
