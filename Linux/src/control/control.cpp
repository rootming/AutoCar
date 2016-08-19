#include "control.h"

Control::Control()
{
    controlList.push_back(this);
    cout << "Add new Control" << endl;
}

Control::~Control()
{
//    for(auto it : controlList){
//        if(it == this){
//            controlList.erase(it);
//        }
//    }
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
        cout << it->getControlName() << endl;
    }
}
