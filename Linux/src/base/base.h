#pragma once
#include <iostream>
using namespace std;

enum DEVICE_TYPE { SENSOR, CONTROLER, MOTOR, OTHER };

class Device
{
public:
    string getDeviceName() const { return name; }
    DEVICE_TYPE getDeviceType() const { return type; }

protected:
    void setDeviceName(string name){ this->name = name; }
    void setDeviceType(DEVICE_TYPE type){ this->type = type; }

private:
    DEVICE_TYPE type;
    string name;


};

class Base
{
public:
    Base()
    {
        if(base == nullptr){
            cerr << "GPIO not init, now init..." << endl;
            initGPIO();
            inited = false;
        }
    }
    void setPin()
    {
        cerr << "Method now implement." << endl;
        // inited = true;
    }
    bool isInit() { return inited; }
    static Base *base;

private:
    void initGPIO();

protected:
    bool inited;

};
