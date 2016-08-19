#include "controller.h"

vector<Controller *> Controller::controllerList;

Controller::Controller()
{
    controllerList.push_back(this);
    cout << "Add new controller" << endl;
}

Controller::~Controller()
{
    for(vector<Controller *>::iterator it = controllerList.begin();
        it != controllerList.end();){
        if(*it == this){
           controllerList.erase(it++);
        }
        else{
            it++;
        }
    }
    cout << "Removed Controller." << endl;
}

void Controller::listController()
{
    for(auto it : controllerList){
        cout << "Controller name:" << it->getControllerName() << "\nType:";
        switch(it->getControllerType()){
        case Controller::SENSOR:
            cout << "SENSOR";
            break;

        case Controller::MOTION:
            cout << "MOTION";
            break;

        case Controller::MISC:
            cout << "MISC";
            break;

        case Controller::OTHER:
            cout << "OTHER";
            break;

        }
        cout << endl;
    }
}
