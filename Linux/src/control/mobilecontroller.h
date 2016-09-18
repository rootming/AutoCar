#pragma once
#include "controller.h"
#include "motor.h"
#include "config.h"
#include <thread>

using namespace std;


class MobileController: public Controller
{
public:
    MobileController();
    ~MobileController();
    void farword();
    void back();
    void brake();
    void turnLeft(const int angle);
    void turnRight(const int angle);
    void spin(const int angle);
    //void goPostion(const Postion &pos);
    void setSpeed(const int speed) { this->speed = speed; }
    void setDelay(const int delay){ this->delay = delay; }

private:
     Motor *motor;
     int speed;
     int delay;
     bool start;
     thread *loop;
     void autoloop();
};
