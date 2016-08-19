#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "base.h"

using namespace std;

class Controller
{
public:
    Controller();
    ~Controller();
    enum CONTROLLER_TYPE { SENSOR, MOTION, MISC, OTHER };
    string getControllerName() const { return name; }
    CONTROLLER_TYPE getControllerType() const { return type; }
    static void listController();
    static vector<Controller *> controllerList;

protected:
    void setControllerName(string name){ this->name = name; }
    void setControllerType(CONTROLLER_TYPE type){ this->type = type; }
    vector<Device *> deviceList;

private:
    CONTROLLER_TYPE type;






    string name;

};
