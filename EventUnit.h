#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "Observer.h"

/*
 * The GoF "Leaf" role for the Composite pattern.
 * 
 * EventUnit is a single operational unit that cannot contain other components
 * (a stage, a booth, a gate, and so on). It is also an Observer because in this design
 * every leaf is interested in hearing about notices form the area that contains it-
 * but each concrete leaf decides for itself, through update(), how it should react
 * This is how the practical achieves "different behaviour through polymorphism, bot type checking"
 * main.cpp and EventGroup never ask "is this a Stage?", they just call update() and open()/close() and 
 * let the object decide itself 
 */

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
