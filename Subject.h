#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Notice;
/**
 * @brief The GoF "Subject" role.
 * 
 * A Subject keeps a list of Observers and can notify all of them at once 
 * when something happens. The Subject does NOT own its Observers- 
 * it just remembers pointers to objects that live somewhere else (usually inside a 
 * Composite ownership tree, or on the stack/heap in main).
 * That is why the destructor below only clears the list instead of deleting anything
 */


class Subject
{
protected:
/// The list of currently-registered, non-owning observer pointers
std::vector<Observer*> observers_;
public:
    ~Subject() {observers_.clear();}

    /**
     * @brief Registers an observer so it will receive future notices
     * 
     * Policy: if the same pointer is already registered, callling attach() again does nothing
     * (no duplicate entries), this keeps notify() from calling update() twice on the same object
     * 
     * @param observer The observer to register. Must not be nullptr
     */
    virtual void attach(Observer* observer);

    /**
     * @brief Removed an observer so it stops receiving notices
     * 
     * Policy: if the observer was never registered(or was already
     * removed), detach() simply does nothing - it is not an error.
     * 
     * @param observer The observer to remove.
     */
    virtual void detach(Observer* observer);

     /**
     * @brief Sends a notice to every currently-registered observer 
     * 
     * We take a snapshot copy of the observer list before looping, so
     * that it is safe even if an observer detaches itself (or another observer) 
     * while being notified
     * 
     * @param notice The notice to broadcast
     */
    virtual void notify(const Notice& notice);
};

#endif