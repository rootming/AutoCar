#pragma once
#include "config.h"
#include "base.h"

class LED: public Base, Device
{
     public:
        explicit LED(const LED &) = delete;
        LED &operator=(const LED &) = delete;
        LED(int brigthness = 0, int range = 0): proBG(brigthness), proRange(range)
        {
            setDeviceName("Front LED");
            setDeviceType(OTHER);
        }
        ~LED();
        void on();
        void off();
        void setPin(int pin);
        int getBrightness(void) const { return proBG; }
        void setBrightness(int brigthness);
    private:
        int proPin;
        int proBG;
        int proRange;

};
