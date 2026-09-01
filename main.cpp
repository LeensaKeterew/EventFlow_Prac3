#include <iostream>
#include "EventControl.h"
#include "EventGroup.h"
#include "Stage.h"
#include "Booth.h"
#include "InfoDesk.h"
#include "Vendor.h"
#include "StaffTeam.h"

int main() {
     std::cout << "===================================================\n";
    std::cout << " TechWave Expo - EventFlow\n";
    std::cout << "===================================================\n\n";

    // ---------------------------------------------------------------
    // 1. Build the Composite ownership tree (sd1).
    // ---------------------------------------------------------------
    std::cout << "--- Building the event structure ---\n";

    EventControl expoControl("TechWave Expo");

    EventGroup* root = new EventGroup("TechWave Expo");

    EventGroup* innovationHall = new EventGroup("Innovation Hall");
    EventGroup* aiZone         = new EventGroup("AI Zone");
    EventGroup* pitchCorner    = new EventGroup("Pitch Corner");
    EventGroup* roboticsZone   = new EventGroup("Robotics Zone");

    EventGroup* startupAlley     = new EventGroup("Startup Alley");
    EventGroup* networkingLounge = new EventGroup("Networking Lounge");

    // Leaves (5 distinct concrete leaf types).
    Stage* pitchStage      = new Stage("Pitch Stage", 80, /*isIndoor=*/true);
    Booth* aiBooth         = new Booth("AI Demo Booth", 30, /*queueThreshold=*/10);
    Stage* roboticsStage   = new Stage("Robotics Stage", 60, /*isIndoor=*/false);
    Booth* roboticsBooth   = new Booth("Robotics Booth", 25, /*queueThreshold=*/8);
    Booth* startupBooth1   = new Booth("Startup Booth 1", 15, /*queueThreshold=*/6);
    Booth* startupBooth2   = new Booth("Startup Booth 2", 15, /*queueThreshold=*/6);
    InfoDesk* helpDesk     = new InfoDesk("Startup Help Desk", 5);
    Vendor* cafeVendor     = new Vendor("Networking Cafe", 40, /*isIndoor=*/true);
    StaffTeam* securityTeam = new StaffTeam("Security Team Alpha", 10);

    // Original feature: give each Stage its own lineup (Task 4.4: lineup rotation).
    pitchStage->addAct("Pitch Stage: Startup Demo Slot A");
    pitchStage->addAct("Pitch Stage: Startup Demo Slot B");
    roboticsStage->addAct("Robotics Stage: Autonomous Drone Show");
    roboticsStage->addAct("Robotics Stage: Robot Soccer Exhibition");

    // Original feature: Booth escalation channel: Security Team Alpha is attached DIRECTLY to AI Demo Booth (not just to its parent group),so it can receive that Booth's own QUEUE_CRITICAL notices (Task 4.4).
    aiBooth->attach(securityTeam);

    // Assemble the tree (Composite ownership). Level count below root: root(0) -> innovationHall(1) -> aiZone(2) -> pitchCorner(3) -> leaves(4)
    pitchCorner->add(pitchStage);
    pitchCorner->add(aiBooth);

    aiZone->add(pitchCorner);
    roboticsZone->add(roboticsStage);
    roboticsZone->add(roboticsBooth);

    innovationHall->add(aiZone);
    innovationHall->add(roboticsZone);

    startupAlley->add(startupBooth1);
    startupAlley->add(startupBooth2);
    startupAlley->add(helpDesk);

    networkingLounge->add(cafeVendor);
    networkingLounge->add(securityTeam);

    root->add(innovationHall);
    root->add(startupAlley);
    root->add(networkingLounge);

    // Observer registration (separate from ownership!): only the three top-level groups register directly with EventControl. Everything below them was already wired up automatically inside add().
    expoControl.attach(innovationHall);
    expoControl.attach(startupAlley);
    expoControl.attach(networkingLounge);

    std::cout << "Event structure built: root owns 3 top-level areas, "
              << "3 levels of nested groups, 9 leaf units.\n\n";

    // ---------------------------------------------------------------
    // 2. Open the whole event (Composite traversal).
    // ---------------------------------------------------------------
    std::cout << "--- Opening the whole event (Composite traversal) ---\n";
    root->open();
    std::cout << "\n";

    std::cout << "--- Full status report (Composite traversal) ---\n";
    root->reportStatus();

    // ---------------------------------------------------------------
    //  3. Ordinary operational notice - schedule change (SD2-style, 2 levels). Also demonstrates the original lineup-rotation feature (Task 4.4): every Stage that receives this advances to the next act in its own lineup_, while InfoDesk (also listening) updates its announcement board.
    // ---------------------------------------------------------------
    std::cout << "\n--- Notice 1: SCHEDULE_CHANGE ---\n";
    expoControl.issueNotice(NoticeType::SCHEDULE_CHANGE,
                             "Startup pitch session moved to 14:00", 0);

    // ---------------------------------------------------------------
    // 4. Capacity-related notice with a condition-based reaction.
    // ---------------------------------------------------------------
    std::cout << "\n--- Notice 2: CAPACITY_ALERT (with different queue lengths) ---\n";
    aiBooth->addToQueue(12);       // long queue -> will suspend
    roboticsBooth->addToQueue(2);  // short queue -> stays open
    expoControl.issueNotice(NoticeType::CAPACITY_ALERT, "Innovation Hall is getting full", 1);

    // ---------------------------------------------------------------
    // 4b: Original feature: Booth escalation channel (Task 4.4). AI Demo Booth's queue grows past CRITICAL (2x its threshold), so this time the same CAPACITY_ALERT also makes the Booth escalate, in its own separate Subject role, straight to Security Team Alpha, a bottom-up notification that never goes through EventControl.
    // ---------------------------------------------------------------
    std::cout << "\n--- Notice 2b: CAPACITY_ALERT again, now past CRITICAL level ---\n";
    aiBooth->addToQueue(10); // total 22, well past 2x the threshold of 10
    expoControl.issueNotice(NoticeType::CAPACITY_ALERT, "Innovation Hall is still getting full", 1);

    std::cout << "\n--- Original feature: aggregate active-staff query (Composite operation) ---\n";
    std::cout << "Staff currently on duty across the whole event: "
              << root->getActiveStaffCount() << "\n";

    // ---------------------------------------------------------------
    // 5: Safety-related notice cascading through 4 runtime levels
    // (EventControl -> Innovation Hall -> AI Zone -> Pitch Corner -> leaves).
    // ---------------------------------------------------------------
    std::cout << "\n--- Notice 3: WEATHER_ALERT (cascades through 4 levels) ---\n";
    expoControl.issueNotice(NoticeType::WEATHER_ALERT, "Thunderstorm approaching the venue", 0);

    // ---------------------------------------------------------------
    // 6: Registration change at runtime - detach then reattach.
    // ---------------------------------------------------------------
    std::cout << "\n--- Registration change: Networking Lounge stops, then resumes, listening ---\n";
    expoControl.detach(networkingLounge);
    std::cout << "[EventControl] Networking Lounge detached (won't hear the next notice).\n";
    expoControl.issueNotice(NoticeType::PAUSE, "Short break before the keynote", 0);
    expoControl.attach(networkingLounge);
    std::cout << "[EventControl] Networking Lounge re-attached.\n";

    // ---------------------------------------------------------------
    // 7: Runtime reorganisation - transfer a booth between groups.
    // ---------------------------------------------------------------
    std::cout << "\n--- Runtime reorganisation: moving Startup Booth 2 ---\n";
    EventComponent* moved = startupAlley->remove(startupBooth2);
    if (moved != nullptr) {
        networkingLounge->add(moved);
        expoControl.logTransfer("Startup Booth 2 moved from Startup Alley to Networking Lounge");
        std::cout << "Startup Booth 2 is now inside Networking Lounge "
                  << "(ownership and observer registration both updated).\n";
    }

    // ---------------------------------------------------------------
    // 8: Emergency scenario followed by recovery (sd4-style).
    // ---------------------------------------------------------------
    std::cout << "\n--- Notice 4: EVACUATE, then RESUME ---\n";
    expoControl.issueNotice(NoticeType::EVACUATE, "Evacuate the venue immediately", 0);
    std::cout << "Staff on duty during the evacuation: " << root->getActiveStaffCount() << "\n";
    expoControl.issueNotice(NoticeType::RESUME, "All clear - event resuming", 0);

    expoControl.printTransferLog();

    // ---------------------------------------------------------------
    // 9: Clean shutdown TIME
    // ---------------------------------------------------------------
    std::cout << "\n--- Clean shutdown ---\n";
    // Policy: Subject does not own its Observers, so before the owned tree is destroyed we detach every top-level group from EventControl. This guarantees EventControl is never left holding a dangling pointer.
    expoControl.detach(innovationHall);
    expoControl.detach(startupAlley);
    expoControl.detach(networkingLounge);

    delete root; // deletes the entire owned subtree exactly once
    root = nullptr;

    std::cout << "\nEvent shutdown complete. No leaks: every owned component was released\n";
    std::cout << "by exactly one delete, driven from the root of the Composite tree.\n";

    return 0;
}