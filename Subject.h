#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject
{
protected:
std::vector<Observer*> observers_;
public:
    ~Subject() {observers_.clear();}
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notify(const Notice& notice);
};

