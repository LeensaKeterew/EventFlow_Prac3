#include "Notice.h"

std::string noticeTypeToString(NoticeType type){
    switch(type){
        case NoticeType::OPEN:return "OPEN";
        case NoticeType::CLOSE:return "CLOS";
        case NoticeType::SCHEDULE_CHANGE:return "SCHEDULE_CHANGE";
        case NoticeType::CAPACITY_ALERT:return "CAPACITY_ALERT";
        case NoticeType::WEATHER_ALERT:return "WEATHER_ALERT";
        case NoticeType::PAUSE:return "PAUSE";
        case NoticeType::RESUME:return "RESUME";
        case NoticeType::EVACUATE:return "EVACUATE";
        case NoticeType::QUEUE_CRITICAL: return "QUEUE_CRITICAL";
    }
    return "UNKNOWN";
}

Notice::Notice(NoticeType type, const std::string& message, int value)
    :type_(type), message_(message), value_(value){}

NoticeType Notice::getType() const {return type_; }

const std::string& Notice::getMessage() const {return message_ ;}

int Notice::getValue() const {return value_;}