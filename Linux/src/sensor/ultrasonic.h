#pragma once
#include <thread>
#include "base.h"

using namespace std;

class UltraSonic: public Base, Device
{
    public:
        explicit UltraSonic(const UltraSonic &) = delete;
        UltraSonic &operator=(const UltraSonic &) = delete;
        UltraSonic();
        void setPin(int trig, int echo);
        void autoScan(void);
        double getDistance(void);
        ~UltraSonic();
    private:
        int proTrigPin;
        int proEchoPin;
        int index;
        bool start;
        double distance[2];
        void autoGetDistance(void);
        thread *scanThread;
//        mutex lock;

};
