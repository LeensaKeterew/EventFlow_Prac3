#ifndef OBSERVER_H
#define OBSERVER_H

class Notice;

/**
 * @brief The GoF "Observer" role.
 * 
 * Anything that wants to be told about notices (weather alerts, capacity
 * warnings, and so on) implements this interface. The Subject that is being watched
 * does not need to know what kind of object the Observer really is-
 * it only calls update().
 * 
 * We use "push": the Subject passes everything the Observer needs inside
 * the Notice object, so the Observer never has to call back into the Subject to ask for more information 
 */

class Observer{
    public:
    virtual ~Observer(){}
    
    /**
     * @brief Called by a Subject when something has changed
     * @param notice The notice describing what happened. The Observer
     *               decides for itself, based on its own type and state, how (or 
     *               whether) to react.
     */
    virtual void update(const Notice& notice)=0;
};

#endif //OBSERVER_H