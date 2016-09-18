#pragma once
#include "controller.h"
#include "brightness.h"
#include "../led/led.h"
#include <thread>

using namespace std;



class LightController: public Controller
{
public:
    LightController();
    ~LightController();
    void setLevel(const int level){ this->level = level; }
    void setDelay(const int delay){ this->delay = delay; }
private:
    LED *light;
    Brightness *sensor;
    thread *loop;
    bool start;
    int level;
    int delay;
    void autoloop();

};
