#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

/**
 * @brief This is the Component in the Composite pattern. It is an abstract base class for all event components, including both composite and leaf nodes.
 * @details It defines the common interface for all event components, allowing them to be treated uniformly.A client can hold a pointer to an EventComponent and call open(), close(), reportStatus() or getCapacity() without ever needing to know whether it is really talking on one stage or an entire zone containing dozens of units.
 */

class EventComponent{
    protected:
        std::string name_;

    public: 
        EventComponent(const std::string& name) : name_(name) {}
        virtual ~EventComponent(){};
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void reportStatus() const = 0;
        virtual int getCapacity() const = 0;


        /** @brief Original feature implemented for task 4.4: get the number of active staff members currently conributing to an on-duty headcount. 
         * This is a Composite operation shared exactly like getCapacity(), a groups answer is the sum of its children's answers but it answers a different question for an organiser("how many security staff are currently on duty?") than getCapacity() does("how many people can this zone hold?"). A default of 0 is given here and only StaffTeam needs to override it. Every other leaf inherits this default unchanged so adding the feature did not require touching Stage, Booth, InfoDesk or Vendor at all.
         * @return The number of active staff members that are on-duty.
         */
        virtual int getActiveStaffCount() const {
            return 0; 
        }
        const std::string& getName() const {
            return name_;
        }

};

#endif