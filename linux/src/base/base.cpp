#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "base.h"

using namespace std;


Base * Base::base = nullptr;

void Base::initGPIO()
{
    if(-1 == wiringPiSetup()){
		cerr << "WiringPi init failed." << endl;
		exit(1);
	}
    base = this;
}