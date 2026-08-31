#ifndef INFO_DESK_H
#define INFO_DESK_H

#include "EventUnit.h"


class InfoDesk:public EventUnit{
    public:
    InfoDesk(const std::string& name, int capacity);
    ~InfoDesk() override;
    void open() override;
    void close() override;
    void reportStatud() const override;
    void update(const Notice& notice) override;

    private:
    std::string announcement_;
};

#endif