#include "motor/motor.h"
#include "sensor/ultrasonic.h"

int main()
{
    Motor test(0);
    UltraSonic test2;
    test2.autoScan();
    return 0;
}