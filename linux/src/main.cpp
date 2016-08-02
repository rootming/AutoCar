#include "motor/motor.h"
#include "led/led.h"
#include "sensor/ultrasonic.h"
#include "sensor/brightness.h"
#include "sensor/temperature.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    UltraSonic us;
    Motor motor(0, 255);
    LED led(100, 255);
    Brightness bg;
    Temperature temp;
    led.setPin(4);
    led.on();
    sleep(1);
    led.off();
    us.setPin(0, 1);
    us.autoScan();
    motor.setPin(2, 3, 22, 23, 24, 25);
    motor.setLeftSpeed(-100);
    motor.setRightSpeed(100);
    sleep(2);
    motor.setLeftSpeed(100);
    motor.setRightSpeed(-100);
    sleep(2);

    for(int i = 0; i < 5; i++){
        cout << us.getDistance() << endl;
        cout << bg.getValue() << endl;
        cout << temp.getValue() << endl;
        sleep(1);
    }
    cin.get();
    return 0;
}
