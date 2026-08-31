#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include <vector>
#include "EventComponent.h"
#include "Observer.h"
#include "Subject.h"

class EventGroup : public EventComponent, public Observer, public Subject {
    private:
        bool open_;
        std::vector<EventComponent*> children_; 

        void printOwnHeader() const;
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
        void update(const Notice&notice) override; 
}; 

#endif