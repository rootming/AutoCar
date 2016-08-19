#include <iostream>
#include <math.h>
#include <wiringPi.h>
#include <pcf8591.h>

#include "config.h"
#include "mypcf8591.h"

bool MyPCF8591::inited = false;

MyPCF8591::MyPCF8591()
{
    if(!inited){
        cerr << "Init PCF8591.\n" << endl;
        pcf8591Setup(ADC_BASE_PIN, ADC_BASE_ADDRESS);
        inited = true;
    }
}
