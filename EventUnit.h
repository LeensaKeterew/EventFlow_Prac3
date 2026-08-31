#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
//#include "Observer.h"

/**
 * @brief The GoF "Leaf" role for the Composite pattern.
 * 
 * EventUnit is a single operational unit that cannot contain other components
 * (a stage, a booth, a gate, and so on). It is also an Observer because in this design
 * every leaf is interested in hearing about notices form the area that contains it-
 * but each concrete leaf decides for itself, through update(), how it should react
 * This is how the practical achieves "different behaviour through polymorphism, bot type checking"
 * main.cpp and EventGroup never ask "is this a Stage?", they just call update() and open()/close() and 
 * let the object decide itself 
 */

class EventUnit : public EventComponent { // , public Observer
    protected:
        int capacity;
        bool active; 

    public: 
        /**
         * @brief Builds a leaf unit.
         * @param name Display name, e.g. "Main Stage".
         * @param capacity How many people this unit can hold/serve at once.
         */
        EventUnit(const std::string& name, int capacity) : EventComponent(name), capacity(capacity), active(false) {}
        ~EventUnit() override{}

        int getCapacity() const override{
            return capacity; 
        }

        //// @return true while this unit is open/active
        bool isActive() const{
            return active; 
        }
        
};

#endif
