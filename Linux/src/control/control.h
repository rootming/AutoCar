#pragma once
#include <iostream>

using namespace std;

enum CONTROL_TYPE { SENSOR, CONTROLER, OTHER };

class Control
{
public:
    string getControlName() const { return name; }
    CONTROL_TYPE getControlType() const { return type; }

protected:
    void setDeviceName(string name);
    void setDeviceType(CONTROL_TYPE type);

private:
    CONTROL_TYPE type;
    string name;

};
