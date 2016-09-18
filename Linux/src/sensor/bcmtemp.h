#pragma once
#include "config.h"
#include "base.h"

class BCMtemp: public Device, Base
{
    public:
        explicit BCMtemp(const BCMtemp &) = delete;
        BCMtemp &operator=(const BCMtemp &) = delete;
        BCMtemp();
        ~BCMtemp(){}
        double getTemp() const;
    private:

};
