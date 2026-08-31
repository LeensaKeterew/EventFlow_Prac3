#ifndef STAGE_H
#define STAGE_H

#include <string>
#include <vector>
#include "EventUnit.h"

/**
 * @brief A concrete Leaf: a performance stage
 * 
 * A stage cares about being paused and resumed, and about whether it is indoors or outdoors
 * An outdoor reacts to a WEATHER_ALERT by pausing itself, while an indoor stage is not affected
 * This is one of the "event rules": the sane WEATHER_ALERT, sent once, produces different reactions
 * because of an object's own state (isIndoor_), not because a controller asked what type it is
 * 
 * Original feature (Task 4.4) - lineup rotation: a stage keeps its own ordered list of upcoming acts.
 * It does not need a new notice type for this- it reacts to the existing SCHEDULE_CHANGE notice by advancing
 * to the next act in its own lineup_ and announcing it, which is genuine new per-object state and behavior than 
 * a renamed existing feature.
 */

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