#include "StaffTeam.h"
#include "Notice.h"
#include <iostream>

StaffTeam::StaffTeam(const std::string& name, int capacity)
    :EventUnit(name, capacity), emergencyMode_(false){}


StaffTeam::~StaffTeam(){
    std::cout << " [destroy] StaffTeam '" << name_ << "' released.\n";
}

void StaffTeam::open(){
    active_ = true;
    std::cout << "  " << name_ << "  (StaffTeam): on duty.\n";
}

void StaffTeam::close(){
    active_ = false;
    std::cout << "  " << name_ << "  (StaffTeam): shift ended\n";
}

void StaffTeam::reportStatus() const{
    std::cout << "  -StaffTeam '" << name_  << "': "
              << (active_ ? (emergencyMode_ ? "on duty, EMERGENCY MODE " : "on duty, normal") : "off duty") << "\n";
}

void StaffTeam::update(const Notice& notice){
    switch(notice.getType()){
        case NoticeType::OPEN:
            open();
            break;
        case NoticeType::CLOSE:
            close();
            break;
        case NoticeType::EVACUATE:
            //Event rule: staff teams remain operation and actually become MORE ACTIVE while everything else around them shuts down
            emergencyMode_ = true;
            active_ = true;
            std::cout << "  " << name_ << "  (StaffTeam): switching to EMERGENCY MODE - assisting evacuation.\n";
            break;
        case NoticeType::RESUME:
            emergencyMode_ = false;
            std::cout << "  " << name_ << "  (StaffTeam): stand down from emergency mode.\n";
            break;
        case NoticeType::QUEUE_CRITICAL:
            //original feature implementation
            active_ = true;
            std::cout << "  " << name_ << "  (StaffTeam): dispatched to " << notice.getMessage() << " for crows control.\n";
            break;
        default:
            std::cout << "  " << name_ << "  (StaffTeam): remaining active regardless.\n";
            break;
    }
}

int StaffTeam::getActiveStaffCount() const {
    return active_ ? 1 : 0;
}