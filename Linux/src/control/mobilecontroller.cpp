#include "mobilecontroller.h"

MobileController::MobileController()
{
    setControllerName("Mobile Controller.");
    setControllerType(Controller::MOTION);
    motor = new Motor(0, 255);
    motor->setPin(2, 3, 22, 23, 24, 25);
    setDelay(DEF_BRAKE_DELAY);
    start = true;
    loop = new thread([&]{ autoloop(); });

}

MobileController::~MobileController()
{

    start = false;

}

void MobileController::farword()
{
    motor->setLeftSpeed(speed);
    motor->setRightSpeed(speed);
}

void MobileController::back()
{
    motor->setLeftSpeed(speed * -1);
    motor->setRightSpeed(speed * -1);

}

void MobileController::brake()
{
    motor->brake();
}

void MobileController::turnLeft(const int angle)
{
    motor->setLeftSpeed(speed / 255 * angle);
    motor->setRightSpeed(speed);

}

void MobileController::turnRight(const int angle)
{
    motor->setLeftSpeed(speed);
    motor->setRightSpeed(speed / 255 * angle);
}


void MobileController::spin(const int angle)
{
    if(angle > 0){
        motor->setLeftSpeed(speed);
        motor->setRightSpeed(speed * -1);
    }
    else{
        motor->setLeftSpeed(speed * -1);
        motor->setRightSpeed(speed);
    }
}

void MobileController::autoloop()
{

    while(start){
        motor->brake();
        this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}


//void MobileController::goPostion(const Postion &pos)
//{



//}


