#include "InfoDesk.h"
#include "Notice.h"
#include <iostream>

    InfoDesk::InfoDesk(const std::string& name, int capacity):EventUnit(name,capacity),announcement_("Welcome to TechWave Expo!"){};
    InfoDesk::~InfoDesk() { 
        std::cout<<" [destroy] InfoDesk '"<<name_<<"' released.\n";
    }
    void InfoDesk::open(){
        active_=true;
        std::cout<<" "<<name_<<" (InfoDesk): OPEN and ready to help.\n";
    }
    void InfoDesk::close() {
        active_=false;
        std::cout<<" "<<name_<<" (InfoDesk): CLOSED.\n";
    }
    void InfoDesk::reportStatus() const {
                std::cout<<" - InfoDesk '"<<name_<<":"<<(active_ ? "open":"closed")<<", announcement=\""<<announcement_<<"\"\n";
    }
    void InfoDesk::update(const Notice& notice){
        switch (notice.getType())
        {
        case NoticeType::SCHEDULE_CHANGE:
            announcement_=notice.getMessage();
            std::cout<<" "<<name_<<" (InfoDesk): announcement board updated to\""<<announcement_<<"\"\n";
            break;
        case NoticeType::EVACUATE:
            active_=false;
            std::cout<<" "<<name_<<"(InfoDesk): directing everyone to exits, then closing.\n";
            break;
        default:
            //Event rule:the info desk stays operational through weather/capacity/pause notices
            //unlike a stage or booth, because visitors still need directions during those events
            std::cout<<" "<<name_<<" (InfoDesk): staying open for visitors.\n";
            break; 
    }
}
