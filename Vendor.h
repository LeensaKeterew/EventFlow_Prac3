#ifndef VENDOR_H
#define VENDOR_H

#include "EventUnit.h"

class Vendor: public EventUnit{
    public:
    Vendor(const std::string& name,int capacity,bool isIndoor);
    ~Vendor() override;
    void open() override;
    void close() override;
    void reportStatus() const override;
    void update(const Notice& notice) override;

    private:
    bool isIndoor_;
    bool serviceAvailable_;
};
#endif