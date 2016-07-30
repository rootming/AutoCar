#include "motor/motor.h"
#include "sensor/ultrasonic.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
//    UltraSonic test2;
    Motor motor(0, 255);
  //  test2.setPin(0, 1);
  //  test2.autoScan();
    motor.setPin(2, 3, 22, 23, 24, 25);
    motor.setLeftSpeed(100);
    motor.setRightSpeed(100);
 //   for(;;){
 //       cout << test2.getDistance() << endl;
 //       sleep(1);
 //   }
    cin.get();
    return 0;
}
