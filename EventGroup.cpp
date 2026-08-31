#include "EventGroup.h"
#include "Notice.h"
#include <iostream>
#include <algorithm>

EventGroup::EventGroup(const std::string& name) : EventComponent(name), open_(false){} 

EventGroup::~EventGroup() {
    std::vector<EventComponent*>::iterator it;

    for(it=children_.begin(); it !=children_.end(); ++it){
        delete *it;
    }

    children_.clear();
    std::cout << " [destroy] EventGroup '" << name_ << "' and its owned subtree released.\n";
}

void EventGroup::open() {
    open_ = true;

    std::vector<EventComponent*>::iterator it;

    for(it=children_.begin(); it !=children_.end(); ++it){
        (*it)->open();
    }
}

void EventGroup::close() {
    open_ = false;

    std::vector<EventComponent*>::iterator it;

    for(it=children_.begin(); it !=children_.end(); ++it){
        (*it)->close();
    }
}

void EventGroup::printOwnHeader() const{
    int total = getCapacity();

    std::cout << name_ << " (" << (open? "open" : "closed") << ", total capacity:" << total << ")\n";
}

void EventGroup::reportStatus() const {
    printOwnHeader();

    std::vector<EventComponent*>::const_iterator it;

    for(it=children_.begin(); it !=children_.end(); ++it){
        (*it)->reportStatus();
    }
}

int EventGroup::getCapacity() const {
    int total = 0; 

    std::vector<EventComponent*>::const_iterator it;

    for(it=children_.begin(); it !=children_.end(); ++it){
        total += (*it)->getCapacity();
    }

    return total;
}

int EventGroup::getActiveStaffCount() const {
    int total = 0; 

    std::vector<EventComponent*>::const_iterator it;

    for(it=children_.begin(); it !=children_.end(); ++it){
        total += (*it)->getActiveStaffCount();
    }

    return total;
} 

void EventGroup::add(EventComponent* child){
    if(child == NULL){
        return;
    }
    children_.push_back(child); 

    Observer* observerChild = dynamic_cast<Observer*>(child); 
    if(observerChild != NULL){
        attach(observerChild);
    }
} 

EventComponent* EventGroup::remove(EventComponent* child){
    auto it = std::find(children_.begin(), children_.end(), child);

    if(it == children_.end()){
        return NULL; 
    }
    children_.erase(it);
    
    Observer* observerChild = dynamic_cast<Observer*>(child); 
    if(observerChild != NULL){
        detach(observerChild);
    }

    return child;
} 

void EventGroup::update(const Notice&notice){
    std::cout << " " << name_ << " (EventGroup) received" << noticeTypeToString(notice.getType()) << " - cascading to " << observers_.size() << " observer(s) below.\n";

    notify(notice); 
}

