#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include <vector>
#include "EventComponent.h"

class EventGroup : public EventComponent {
    private:
        bool open_;
        std::vector<EventComponent*> children; 

    public: 
        EventGroup(const std::string& name); 
        ~EventGroup() override;
        void open() override;
        void close() override;
        void reportStatus() const override;
        int getCapacity() const override;
        int getActiveStaffCount() const override; 
        void add(EventComponent* child); 
        EventComponent* remove(EventComponent* child); 

}; 

#endif