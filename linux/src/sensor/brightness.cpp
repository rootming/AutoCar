#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "../config/config.h"
#include "brightness.h"

Brightness::Brightness()
{
    pcf8591Setup(_BG_PIN, _ADC_ADDRESS);
    pinMode(_BG_PIN + 1, INPUT);
}

int Brightness::getValue(void)
{
    return analogRead(_BG_PIN + 1);
}