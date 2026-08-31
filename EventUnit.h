#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "Observer.h"

class EventUnit : public EventComponent, public Observer { 
    protected:
        int capacity_;
        bool active_; 

    public: 
        // Builds a leaf unit with a name and capacity.
        EventUnit(const std::string& name, int capacity) : EventComponent(name), capacity_(capacity), active_(false) {}
        ~EventUnit() override{}

        int getCapacity() const override{
            return capacity_; 
        }

        //true while this unit is open/active
        bool isActive() const{
            return active_; 
        }
        
};

#endif
