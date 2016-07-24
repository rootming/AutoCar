#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <cstdlib>

using namespace std;

const int _LED_PIN = 0;
const int _RANGE = 255;


int main()
{
	if(-1 == wiringPiSetup()){
		cerr << "WiringPi init failed." << endl;
		exit(1);
	}
	softPwmCreate(_LED_PIN, 0, _RANGE);
	for(;;){
		for(int i = 0; i < _RANGE; i++){
			softPwmWrite (_LED_PIN, i);
			delay(50);
		}
		for(int i = _RANGE; i > 0; i--){
			softPwmWrite (_LED_PIN, i);
			delay(50);
		}

	}
}