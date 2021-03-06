#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Device
{
public:
    explicit Device(const Device &) = delete;
    Device &operator=(const Device &) = delete;
    Device();
    virtual ~Device();
    enum DEVICE_TYPE { SENSOR, MOTOR, MISC, OTHER };
    string getDeviceName() const { return name; }
    DEVICE_TYPE getDeviceType() const { return type; }
    static void listDevice();
    static vector<Device *> deviceList;
    virtual bool selfCheck();

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

struct Postion
{
    int32_t x, y;
};
