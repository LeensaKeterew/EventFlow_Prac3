#ifndef VENDOR_H
#define VENDOR_H

#include "EventUnit.h"

/**
 * @briefA concrete Leaf: a food/drink vendor.
 * 
 * Like Stage, a Vendor cares whether it is indoors or outdoors, but its 
 * role is "serving", not "performing", so its reactions are worded and triggered differently even though the underlying idea is similar-
 * this shows the same rule expressed through independent leaf types rather than a shared "outdoor unit" base class doing the deciding 
 */
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