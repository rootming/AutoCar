#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <cstdlib>
#include "led.h"

using namespace std;

LED::~LED()
{
	if(proRange == 0)
		digitalWrite(proPin, LOW);
	else
		softPwmStop(proPin);
}


void LED::setPin(int pin)
{
	inited = true;
	proPin = pin;
	if(proRange == 0){
		pinMode(proPin, OUTPUT);
		digitalWrite(proPin, LOW);
	}else{
		softPwmCreate(proPin, 0, proRange);
	}

}

void LED::setBrightness(int brigthness)
{
	if(proRange == 0){
		cerr << "Not support.\n";
		return;
	}
	proBG = brigthness;
	softPwmWrite(proPin, proBG);
}

void LED::on()
{
	if(proRange == 0){
		digitalWrite(proPin, HIGH);
	}else{
		softPwmWrite(proPin, proBG);
	}
}


void LED::off()
{
	if(proRange == 0){
		digitalWrite(proPin, LOW);
	}else{
		softPwmWrite(proPin, 0);
	}
}