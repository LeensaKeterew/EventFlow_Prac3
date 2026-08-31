#include "Vendor.h"
#include "Notice.h"
#include <iostream>

Vendor::Vendor(const std::string& name,int capacity,bool isIndoor):EventUnit(name,capacity),isIndoor_(isIndoor),serviceAvailable_(true){}

    Vendor::~Vendor(){
        std::cout<<" [destroy] Vendor '"<<name_<<"' released.\n";
    }
    void Vendor::open(){
        active_=true;
        serviceAvailable_=true;
        std::cout<<"  "<<name_<<" (Vendor): stall OPEN.\n";
    }
    void Vendor::close() {
        active_=false;
        serviceAvailable_=false;
        std::cout<<"  "<<name_<<" (Vendor): stall CLOSED.\n";      
    }

    void Vendor::reportStatus() const{
        std::cout<<" - Vendor '"<<name_<<":"<<(active_ ? (serviceAvailable_?"open,serving":"open,service suspended"):"closed")<<", indoor="<<(isIndoor_? "yes":"no")<<"\n";
    }
    void Vendor::update(const Notice& notice){
        switch (notice.getType()){
            case NoticeType::OPEN:
                open();
                break;
            case NoticeType::CLOSE:
                close();
                break;
            case NoticeType::WEATHER_ALERT:
                if (!isIndoor_){
                    serviceAvailable_=false;
                    std::cout<<" "<<name_<<" (Vendor,outdoor): packing away stock - "<<notice.getMessage()<<"\n";
                } else {
                    std::cout<<"  "<<name_<<" (Vendor,indoor): unaffected, still serving.\n";
                }
                break;
            case NoticeType::EVACUATE:
                active_=false;
                serviceAvailable_=false;
                std::cout<<" "<<name_<<" (Vendor): EVACUATE - stall shut down.\n";
                break;
            default:
                break;
            
        }
    }
