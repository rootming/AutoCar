#pragma once
#include "config.h"
#include "base.h"


class MyPCF8591: public Base, Device
{
    public:
        explicit MyPCF8591(const MyPCF8591 &) = delete;
        MyPCF8591 &operator=(const MyPCF8591 &) = delete;
        MyPCF8591();
        ~MyPCF8591(){}
        void setAddr(int addr){ proAddr = addr; }
        virtual int getValue(void) = 0;
        static bool inited;
    protected:
//        int proBaseAddr;
        int proAddr;

};
