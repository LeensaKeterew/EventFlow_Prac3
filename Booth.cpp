#include "Booth.h"
#include "Notice.h"
#include <iostream>

Booth::Booth(const std::string& name, int capacity, int queueThreshold)
    : EventUnit(name, capacity), queueThreshold_(queueThreshold),
queueLength_(0), suspended_(false){}

Booth::~Booth(){
    std::cout << " [destroy] Booth '" << name_ << " 'released.\n";
}

void Booth::open(){
    active_ = true;
    suspended_ = false;
    std::cout << "  " << name_ << " (Booth): now OPEN for visitors.\n";
}

void Booth::close(){
    active_ = false;
    std::cout<< "  " << name_ << " (Booth): CLOSED.\n";
}

void Booth::reportStatus() const {
    std::cout << " - Booth '" << name_ << "': "
              << (active_ ? (suspended_ ? "open but SUSPENDED (queue too long)" : "open and serving" ): "closed")
              << ", queue=" << queueLength_ << "/" << queueThreshold_
              << ", capacity=" << capacity_ << "\n";
}

void Booth::addToQueue(int people){
    queueLength_ += people;
}

void Booth::update(const Notice& notice){
    switch(notice.getType()){
        case NoticeType::OPEN:
            open();
            break;
        case NoticeType::CLOSE:
            close();
            break;
        case NoticeType::CAPACITY_ALERT:
        //this is only suspended if the queue is long enough. This is a condition-based decision.
            if(queueLength_ >= queueThreshold_){
                suspended_ = true;
                std::cout << " " << name_ << " (Booth): queue (" << queueLength_
                          << ") is past the threshold - service SUSPENDED.\n";
                          //implementation of the original feature mentioned. Escalation. If the queue is at CRITICAL level (double the ordinary threshold), this Booth raises its own notice, in its separate Subject role and then straight to whoever is directly attached to it AND DOES NOT GO ANYWHERE NEAR THE EVENTCONTROL. 
                          if(queueLength_ >= queueThreshold_ * 2){
                            Notice critical(NoticeType::QUEUE_CRITICAL, name_ + " queue is critical (" + std::to_string(queueLength_) + " waiting)");

                            std::cout<< " " << name_ << " (Booth, as Subject): escalating directly to " << observers_.size() << " attached observer(s).\n ";

                            notify(critical);
                          }
            }
            else {
                std::cout<< " " << name_ << " (Booth): queue is short(" <<queueLength_ << ") - staying open despite the alert.\n";
            }
            break;
        case NoticeType::EVACUATE: 
            active_ = false;
            suspended_ = true;
            std::cout << " " << name_ << " (Booth): EVACUATING - packing up now.\n";
            break;
        default:
            break;
    }
}