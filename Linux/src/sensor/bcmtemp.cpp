#include "bcmtemp.h"
#include <fstream>
#include <cstdlib>

using namespace std;

BCMtemp::BCMtemp()
{
    setDeviceName("BCM Temporary Sensor");
    setDeviceType(SENSOR);
}



double BCMtemp::getTemp() const
{
    string raw;
    ifstream file(DEF_BCM_TEMP_FILE, ios::binary | ios::trunc | ios::in);
    if(!file.is_open())
        return 0.0;
    file >> raw;
    return atof(raw.c_str());
}
