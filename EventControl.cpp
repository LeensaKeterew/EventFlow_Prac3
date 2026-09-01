#include "EventControl.h"
#include "Notice.h"
#include <iostream>

EventControl::EventControl(const std::string& eventName)
    : eventName_(eventName) {}

void EventControl::issueNotice(NoticeType type, const std::string& message, int value){
    Notice notice(type, message, value);
    std::cout<< "\n[EventControl] " << eventName_ << " issues " << 
    noticeTypeToString(type) << ": \"" << message << "\n'\n";
    notify(notice);
}

void EventControl::logTransfer(const std::string& description){
    transferLog_.push_back(description);
}

void EventControl::printTransferLog() const {
    std::cout << "\n[EventControl] Reorganisation log (" << transferLog_.size() << " entr"
              << (transferLog_.size() == 1 ? "y" : "ies") << "):\n";
    for (const std::string& entry : transferLog_) {
        std::cout << "  - " << entry << "\n";
    }
}