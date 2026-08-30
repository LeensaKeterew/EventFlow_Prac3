#ifndef BOOTH_H
#define BOOTH_H

#include "EventUnit.h"
#include "Subject.h"

/*Thi is the concrete Leaf: an exhibition/vendor booth 
-> Implementation of Task 4.3 feature: a Booth tracks its own queue length. So basically when CAPACITY_ALERT arrives, it only suspends service if its queue  is already at or past a threshold(implementing the "if capacity >= threshold"), also a quiet booth with a short queue is allowed to keep serving people even during a gneral capacity warning. 

-> One additional feature found here for Task 4.4 is the Booth queue escalation
    -> Normally, notices only travel top-down, EventControl tells a zone, the zone tells its booth and stages but we wanted booths to be able to ask for help on their own, without waiting for the control room. So we made Booth a Subject ad well as an Observer. It it already listens for notices like everyone else, but it can ALSO send its own notice out. SO if a booth's queue gets really long(double its nomal "suspend limit"), it starts off a QUEUE_CRITICAL notice straight to whichever StaffTeam is attached to it, asking for crow control. EventControl never even knows this happened, as a direct line between the booth and it's security team. 
    -> Helpful cause this means a StaffTeam can be listening to 2 different Subjects at once: its zone(for normal notices like WEATHER_ALERT) and a specific booth(for this emergeny queue alert). */

class Booth : public EventUnit, public Subject {
    public:
        Booth(const std:string &name, int capacity , int queueThreshold);
        ~Booth() override;

        void open() override;
        void close() override;
        void reportStatus() const override;
        void update(const Notice & notice) override;

        void addToQueue(int people); //using this to stimulate people joining the queue which is for testing

    private:
        int queueThreshold_;
        int queueLength_;
        bool suspended_;
};

#endif
