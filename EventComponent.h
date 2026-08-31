#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

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
        
        virtual int getActiveStaffCount() const {
            return 0; 
        }
        const std::string& getName() const {
            return name_;
        }

};

#endif