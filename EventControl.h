#ifndef EVENT_CONTROL_H
#define EVENT_CONTROL_H

#include <vector>
#include <string>
#include "Subject.h"
#include "Notice.h"

/**
 * @brief The event's central control room
 * 
 * EventControl is a ConcreteSubject and it represents the people running the event. Now we chose to keep it OUTSIDE the Composite tree entirely because it does not have a capacity or open/closed state of it own; it only issues notices to whichever top-level EventGroups have registered with it. Our other original feature is where EventControl keeps a simple text log og every runtime reorganisation(unit transferes between groups), so  we can see the history of what happened during the event. 
 */

 class EventControl : public Subject {
    public:
        explicit EventControl(const std::string& eventName);
        
        void issueNotice(NoticeType type, const std::string& message, int value=0);

        void logTransfer(const std::string& description);
        void printTransferLog() const;
    
    private: 
        std::string eventName_;
        std::vector<std::string> transferLog_; 

};

#endif