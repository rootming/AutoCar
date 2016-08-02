#pragma once
#include "config.h"
#include "mypcf8591.h"

class Temperature: public MyPCF8591
{
     public:
        explicit Temperature(const Temperature &) = delete;
        Temperature &operator=(const Temperature &) = delete;
        Temperature();
        ~Temperature(){}
        int getValue(void);        
    
};
