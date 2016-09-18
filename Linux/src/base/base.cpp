#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <mutex>
#include "base.h"

using namespace std;

vector<Device *> Device::deviceList;

Base * Base::base = nullptr;


Device::Device()
{
    deviceList.push_back(this);
    cout << "Add new device." << endl;
}

Device::~Device()
{
    for(vector<Device *>::iterator it = deviceList.begin();
        it != deviceList.end();){
        if(*it == this){
           deviceList.erase(it++);
        }
        else{
            it++;
        }
    }
    cout << "Removed device." << endl;
}

void Device::listDevice()
{
    for(auto it : deviceList){
        cout << "Device name:" << it->getDeviceName() << "\nType:";
        switch(it->getDeviceType()){
        case Device::MISC:
            cout << "MISC";
            break;

        case Device::MOTOR:
            cout << "MOTOR";
            break;

        case Device::SENSOR:
            cout << "SENSOR";
            break;
        case Device::OTHER:
            cout << "OTHER";
            break;
        }
        cout << endl;
    }
}

void Base::initGPIO()
{
    if(-1 == wiringPiSetup()){
		cerr << "WiringPi init failed." << endl;
		exit(1);
	}
    base = this;
}
