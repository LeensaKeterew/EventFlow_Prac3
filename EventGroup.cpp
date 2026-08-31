#include "EventGroup.h"
#include "Notice.h"
#include <iostream>
#include <algorithm>

EventGroup::EventGroup(const std::string& name) : EventComponent(name), open_(false){} 

EventGroup::~EventGroup() {
    std::vector<EventComponent*>::iterator it;

    for(it=children.begin(); it !=children.end(); ++it){
        delete *it;
    }

    children.clear();
    std::cout << " [destroy] EventGroup '" << name << "' and its owned subtree released.\n";
}

void EventGroup::open() {
    open_ = true;

    std::vector<EventComponent*>::iterator it;

    for(it=children.begin(); it !=children.end(); ++it){
        (*it)->open();
    }
}

void EventGroup::close() {
    open_ = false;

    std::vector<EventComponent*>::iterator it;

    for(it=children.begin(); it !=children.end(); ++it){
        (*it)->close();
    }
}

void EventGroup::reportStatus() const {

}

int EventGroup::getCapacity() const {
    int total = 0; 

    std::vector<EventComponent*>::const_iterator it;

    for(it=children.begin(); it !=children.end(); ++it){
        total += (*it)->getCapacity();
    }

    return total;
}

int EventGroup::getActiveStaffCount() const {
    int total = 0; 

    std::vector<EventComponent*>::const_iterator it;

    for(it=children.begin(); it !=children.end(); ++it){
        total += (*it)->getActiveStaffCount();
    }

    return total;
} 

void EventGroup::add(EventComponent* child){

} 

EventComponent* EventGroup::remove(EventComponent* child){
    auto it = std::find(children.begin(), children.end(), child);

    if(it == children.end()){
        return NULL; 
    }

    children.erase(it); 


} 

void EventGroup::update(const Notice&notice){

}

