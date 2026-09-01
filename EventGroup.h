#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include <vector>
#include "EventComponent.h"
#include "Observer.h"
#include "Subject.h"

/**
 * @brief THis is the GoF Composite role. 
 * 
 * An EventGroup is part of the event that contains other parts, like a hall, a zone, or a corner made of a few units. 
 * 
 * IT ALSO plays 2 Observer pattern roles, for 2 different reasons: 
 *  -> It is a Subject to the things directly inside it, its children, beacuse when it receives a notice it must be able to pass that notice down to whichever of its children are interested. 
 * 
 * -> It is an Observer to whatever contains IT(the parent group, or EventControl at the top level), beacuse it needs to be told about notices coming from above so that it can cascade them downward.
 * 
 * Our design choice was between ownership vs observing: adding a child to this group with add() makes the group OWN that child(it will delete it) and if the child is also an Observer, it automitically registers it to receive this group's notice too. We chose to couple ownership and observation this way beacuse in this event, "being physically located inside an area" and "wanting to hear that area's announcements " are the same thing for every unit in our design.
 */

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