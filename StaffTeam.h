#ifndef STAFF_TEAM_H
#define STAFF_TEAM_H

#include "EventUnit.h"

/** @brief A concrete leaf, a staff team(security, medical and others).
 * 
 * @details Idea is from the specification where a staff team stays operational during an alert that pauses stages and suspends vendors. On EVACUATE it does the opposite of everyone else instead of closing and then switches into "emergency mode" and becomes more active. 
 */

class StaffTeam : public EventUnit {
    public:
        StaffTeam(const std::string& name, int capacity);
        ~StaffTeam() override;
        void open() override;
        void close() override;
        void reportStatus() const override;
        void update(const Notice& notice) override;

        /** @brief the extra original feature for Task 4.4: 1 while on duty, 0 otherwise, the leaf-level contribution to EventGroup::getActiveStaffCount(). */
        int getActiveStaffCount() const override;

    private:
        bool emergencyMode_; 

};

#endif