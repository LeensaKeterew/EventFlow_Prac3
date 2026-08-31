#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
//#include "Observer.h"

class EventUnit : public EventComponent { // , public Observer
    protected:
        int capacity;
        bool active; 

    public: 
        EventUnit(const std::string& name, int capacity) : EventComponent(name), capacity(capacity), active(false) {}
        ~EventUnit() override{}

        int getCapacity() const override{
            return capacity; 
        }
        bool isActive() const{
            return active; 
        }
        
};

#endif
