#pragma once
#include "../config/config.h"
#include "../base/base.h"

class Brightness: public Base
{
    public:
        explicit Brightness(const Brightness &) = delete;
        Brightness &operator=(const Brightness &) = delete;
        Brightness();
        ~Brightness(){};
        void setAddr(int addr);
        int getValue(void);

        
    private:
        int proAddr;
};
