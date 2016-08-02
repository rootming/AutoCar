#pragma once
#include <iostream>
using namespace std;

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
