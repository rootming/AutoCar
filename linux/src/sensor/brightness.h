#pragma once

class Brightness
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
