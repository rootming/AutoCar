#pragma once
#include "config.h"
#include "base.h"
#include "mypcf8591.h"

class Brightness: public MyPCF8591, Device
{
    public:
        explicit Brightness(const Brightness &) = delete;
        Brightness &operator=(const Brightness &) = delete;
        Brightness();
        ~Brightness(){}
        int getValue(void);        
    // private:
    //     int proAddr;
};
