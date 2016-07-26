#include <wiringPi.h>
#include <softPwm.h>

#include "ultrasonic.h"
#include "../config/config.h"

UltraSonic::UltraSonic()
{
    scanThread = nullptr;
    index = 0;
    start = false;

}

UltraSonic::~UltraSonic()
{
    start = false;
    if(scanThread != nullptr)
        delete scanThread;
}

void UltraSonic::setPin(int trig, int echo)
{
    proTrigPin = trig;
    proEchoPin = echo;
    inited = true;
    pinMode(proTrigPin, OUTPUT);
    pinMode(proEchoPin, INPUT);
    digitalWrite(proTrigPin, LOW);
}


void UltraSonic::autoScan(void)
{
    if(!isInit()){
        cerr << "Need set PIN." << endl;
        return;
    }
    start = true;
    scanThread = new thread([&]{ autoGetDistance(); });
}

double UltraSonic::getDistance(void)
{
    return distance[index];
}

void UltraSonic::autoGetDistance(void)
{
    cerr << "Auto scan start.\n";
    while(start == true){
        digitalWrite(proTrigPin, HIGH);
        delayMicroseconds(20);
        digitalWrite(proTrigPin, LOW);

        //Wait for echo start
        while(digitalRead(proEchoPin) == LOW);
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(proEchoPin) == HIGH);
        long travelTime = micros() - startTime;

        //Get distance in cm
        index = (index + 1) % 2;
        distance[index] = travelTime / 58;
        std::this_thread::sleep_for (std::chrono::milliseconds(_SR_SCAN_DELAY));
    }
    cerr << "Auto scan stop.\n";
 
}
