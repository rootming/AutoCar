#pragma once
#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

enum CONTROL_TYPE { SENSOR, CONTROLER, OTHER };

class Control
{
public:
    Control();
    ~Control();
    string getControlName() const { return name; }
    CONTROL_TYPE getControlType() const { return type; }
    static void listControl();
    static vector<Control *> controlList;
protected:
    void setControlName(string name){ this->name = name; }
    void setControlType(CONTROL_TYPE type){ this->type = type; }

private:
    CONTROL_TYPE type;
    string name;

};
