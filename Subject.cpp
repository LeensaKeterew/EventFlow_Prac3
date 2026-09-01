#include "Subject.h"
#include "Notice.h"
#include <algorithm>

void Subject::attach(Observer* observer){
    if (observer==nullptr){
        return;
    }
    bool alreadyThere= std::find(observers_.begin(),observers_.end(),observer)!=observers_.end();
    if (!alreadyThere){
        observers_.push_back(observer);
    }
}

void Subject::detach(Observer* observer){
    observers_.erase(std::remove(observers_.begin(),observers_.end(),observer),observers_.end());
}

void Subject::notify(const Notice& notice){
    std::vector<Observer*> snapshot=observers_;
    for (Observer* observer:snapshot){
        observer->update(notice);
    }
}