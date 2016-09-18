#pragma once
#include "config.h"
#include "base.h"


class Motor: public Base, Device
{
    public:
        // enum Mode { ONE_STEP, TWO_STEP };
        // Motor(int pin, int speed = 0, Mode mode = ONE_STEP, int range = 255);
        explicit Motor(const Motor &) = delete;
        Motor &operator=(const Motor &) = delete;
        Motor(int speed, int range = 255);
        void setPin(int left = MOTOR_LEFT_PIN, int right = MOTOR_RIGHT_PIN,
                int INT0 = MOTOR_INT0_PIN, int INT1 = MOTOR_INT1_PIN,
            int INT2 = MOTOR_INT2_PIN, int INT3 = MOTOR_INT3_PIN);
        // void setMode(Mode mode) { proMode = mode; };
        virtual void setLeftSpeed(int speed);
        virtual void setRightSpeed(int speed);
        virtual void brake(void) {}
        ~Motor();
        // Mode getMode(void) { return proMode; };
    private:
        int proLeftPin;
        int proRightPin;
        int proINT0;
        int proINT1;
        int proINT2;
        int proINT3;
        int proLeftSpeed;
        int proRightSpeed;
        int proRange;
//        int proDelay;

        // Mode proMode;

};
