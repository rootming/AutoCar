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
    cout << "Add new Control" << endl;
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
}

void Device::listDevice()
{
    for(auto it : deviceList){
        cout << it->getDeviceName() << endl;
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
