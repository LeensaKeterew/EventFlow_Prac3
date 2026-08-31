#ifndef OBSERVER_H
#define OBSERVER_H

class Notice;

class Observer{
    public:
    virtual ~Observer(){}
    
    virtual void update(const Notice& notice)=0;
};

#endif //OBSERVER_H