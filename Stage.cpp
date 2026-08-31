#include "Stage.h"
#include "Notice.h"
#include <iostream>

    Stage::Stage(const std::string& name, int capacity, bool isIndoor):EventUnit(name,capacity),isIndoor_(isIndoor),paused(false),currentActIndex_(0){}
    
    Stage::~Stage(){
        std::cout<<" [destroy] Stage '"<<name_<<"' released.\n";
    };

    void Stage::open() {
        active_=true;
        paused_=false;
        std::cout<<" "<<name_<<"' (Stage): performance schedule is now OPEN.\n";

    }
    void Stage::close(){
        active_=false;
        std::cout<<" "<<name_<< " (Stage): CLOSED for the day.\n";
    }
    void Stage::reportStatus() const{
        std::cout<<" - Stage '"<<name_<<"': "<<(active_? ("open but PAUSED" : "open and running"):"closed")<<",indoor="<<(isIndoor_? "yes":"no")<<", capacity="<<capacity_<<"\n";
    }

    void Stage::update(const Notice& notice){
        switch(notice.getType()){
            case NoticeType::OPEN:
                open();
                break;
            case NoticeType::CLOSE:
                close()
                break;
            case NoticeType::PAUSE:
                paused_=true;
                std::cout<<name_<<" (Stage): performance PAUSED - "<<notice.getMessage()<<"\n";
                break;
            case NoticeType::RESUME:
                paused_=false;
                std::cout<<name_<<" (Stage): performance RESUMED.\n ";
            case NoticeType::WEATHER_ALERT:
                if (!isIndoor_){
                    paused_=true;
                    std::cout<<" "<<name_<<" (Stage, outdoor): pausing show for weather - "<<notice.getMessage()<<"\n";
                } else{
                    std::cout<<" "<<name_<<" (Stage, indoor): weather alert does not affect us.\n";
                }
                break;
            case NoticeType::EVACUATE:
                paused_=true;
                active_=false;
                std::cout <<" "<<name_<<" (Stage): EVACUATING - show stopped immediately.\n";
                break;
            case NoticeType::SCHEDULE_CHANGE:
                if (currentActIndex_<lineup_.size()){
                    std::cout<<" "<<name_<<" (Stage): Schedule change - now is up\""<<lineup_[currentActIndex_]<<"\".\n";
                    ++currentActIndex_;
                } else{
                    std::cout<<" "<<name_<<" (Stage): schedule change - no more acts in the lineup.\n";

                }
                break;

            default:
            //capacity alerts are not relevant to stage's own reaction.
                break;
        }
    }

    void Stage::addAct(const std::string& actName){
        lineup_.push_back(actName);
    }
