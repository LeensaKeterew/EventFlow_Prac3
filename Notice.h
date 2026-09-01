#ifndef NOTICE_H
#define NOTICE_H
#include <string>

/** @brief This manages the different kinds of announcements that EventControl can send out in the notification
 * 
 * @details EventUnit decides for itself how it reacts to each one and the Subject does not know or care what the reaction will be.
 */
enum class NoticeType {
    OPEN,
    CLOSE,
    SCHEDULE_CHANGE,
    CAPACITY_ALERT,
    WEATHER_ALERT, // bad weather is affecting outdoor areas
    PAUSE,
    RESUME,
    EVACUATE,
    QUEUE_CRITICAL //A Booth's own escalation notice which is raised directly to whichever StaffTeam is attached to it(bottom up, not issued by EventControl)
};


/** @brief basically used for the demo where it turns a NoticeType into readable word. */
std::string noticeTypeToString(NoticeType type);


/** @brief the class is a single notice/order that travels from a Subject to its Observers
 * @details Basically we use the "push" style of Observers: the Subject fills in this object with everything an Observer could need and hands it straight to update. The Observer never has to call back into the Subject to ask "what happened" as it already knows.
 */

class Notice {
    public:
        Notice(NoticeType type, const std::string& message, int value =0);
        NoticeType getType() const;
        const std::string& getMessage() const;
        int getValue() const; // a value attached to the notice


    private:
        NoticeType type_;
        std::string message_;
        int value_;
};

#endif