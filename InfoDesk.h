#ifndef INFO_DESK_H
#define INFO_DESK_H

#include "EventUnit.h"

/**
 * @brief A concrete Leaf: a help/information desk.
 * 
 * An InfoDesk keeps handing out information through almost everythin-
 * it only truly closes on EVACUATE. On a SCHEDULE_CHANGE it updates the
 * announcement it is displaying to visitors.
 */

class InfoDesk:public EventUnit{
    public:
    InfoDesk(const std::string& name, int capacity);
    ~InfoDesk() override;
    void open() override;
    void close() override;
    void reportStatus() const override;
    void update(const Notice& notice) override;

    private:
    std::string announcement_;
};

#endif