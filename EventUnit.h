#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "Observer.h"


/**
 * @brief This is the Leaf role for the Composite pattern. It represents a single unit of the event that has a capacity and can be open or closed.
 * @details It also plays the Observer role in the Observer pattern, allowing it to receive notices from its parent EventGroup or from EventControl. But each concrete leaf decides for itself, through update(), how it should react. This achieves "different behaviours through polymorphism" as it never aks "what happened" back to the Subject, it just reacts based on its own type and state and let the object itself decide what to do.
 */
class EventUnit : public EventComponent, public Observer { 
    protected:
        int capacity_;
        bool active_; 

    public: 
        
        EventUnit(const std::string& name, int capacity) : EventComponent(name), capacity_(capacity), active_(false) {}
        ~EventUnit() override{}

        int getCapacity() const override{
            return capacity_; 
        }

        /// @return true while this unit is open/active
        bool isActive() const{
            return active_; 
        }
        
};

#endif
