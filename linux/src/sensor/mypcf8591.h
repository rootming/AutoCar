#pragma once
#include "../config/config.h"
#include "../base/base.h"


class MyPCF8591: public Base
{
    public:
        explicit MyPCF8591(const MyPCF8591 &) = delete;
        MyPCF8591 &operator=(const MyPCF8591 &) = delete;
        MyPCF8591();
        ~MyPCF8591(){};
        void setAddr(int addr){ proAddr = addr; }
        virtual int getValue(void) = 0;
        static bool inited;
    protected:
//        int proBaseAddr;
        int proAddr;

};
