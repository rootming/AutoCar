#include "motor/motor.h"
#include "sensor/ultrasonic.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    Motor test(0);
    UltraSonic test2;
    test2.setPin(0, 1);
    test2.autoScan();
    for(;;){
        cout << test2.getDistance() << endl;
        sleep(1);
    }
    return 0;
}
