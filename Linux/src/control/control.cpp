#include "control.h"

vector<Control *> Control::controlList;

Control::Control()
{
    controlList.push_back(this);
    cout << "Add new Control" << endl;
}

Control::~Control()
{
    for(vector<Control *>::iterator it = controlList.begin();
        it != controlList.end();){
        if(*it == this){
           controlList.erase(it++);
        }
        else{
            it++;
        }
    }
}

void Control::listControl()
{
    for(auto it : controlList){
        cout << "Control name:" << it->getControlName() << ", type:";
        switch(it->getControlType()){
        case Control::SENSOR:
            cout << "SENSOR";
            break;

        case Control::MOTION:
            cout << "MOTION";
            break;

        case Control::OTHER:
            cout << "OTHER";
            break;

        }
        cout << endl;
    }
}
