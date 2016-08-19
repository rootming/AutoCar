#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "base.h"

using namespace std;



class Control
{
public:
    Control();
    ~Control();
    enum CONTROL_TYPE { SENSOR, CONTROLER, OTHER };
    string getControlName() const { return name; }
    CONTROL_TYPE getControlType() const { return type; }
    static void listControl();
    static vector<Control *> controlList;

protected:
    void setControlName(string name){ this->name = name; }
    void setControlType(CONTROL_TYPE type){ this->type = type; }
    vector<Device *> deviceList;

private:
    CONTROL_TYPE type;
    string name;

};
