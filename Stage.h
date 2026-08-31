#ifndef STAGE_H
#define STAGE_H

#include <string>
#include <vector>
#include "EventUnit.h"

class Stage: public EventUnit{
    public:
    Stage(const std::string& name, int capacity, bool isIndoor);
    ~Stage() override;
    void open() override;
    void close() override;
    void reportStatus() const override;
    void update(const Notice& notice) override;
    //// @brief Adds an act to the end of this stage's lineup (used by main.cpp).
    void addAct(const std::string& actName);

    private:
    bool isIndoor_;
    bool paused_;
    std::vector<std::string> lineup_;
    std::size_t currentActIndex_;
}

#endif