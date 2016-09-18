#include "lightcontroller.h"
#include "config.h"

LightController::LightController()
{
    setControllerName("Light Controller.");
    setControllerType(Controller::MISC);
    light = new LED(100, 255);
    sensor = new Brightness();
    light->setPin(4);

    setLevel(DEF_LEVEL);
    setDelay(DEF_DELAY);
    start = true;
    loop = new thread([&]{ autoloop(); });
}



LightController::~LightController()
{
    start = false;

}

void LightController::autoloop()
{
    while(start){
        if(sensor->getValue() < level){
            light->on();
        }
        else{
            light->off();
        }
        this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

}
