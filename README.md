# EventFlow_Prac3
The practical is about creating Eventful app. Eventful is a reusable event coordination system that helps different parts of an event, such as zones, stages, gates, vendors and staff, commuicate  and coordinate. Using C++11 to implement the system and UML diagrams to show how the object interact. 

# Team Members
Nokhaya Foloti (u24578071)
Joelle Tsaku (u24984362)
Leensa Keterew (u24577988)

# Description
TeachWave Expo is a technology exhibition made up of nested areas, a hall containing zones, zones containing corners, corners containing stages and booths and more. A central room, `EventControl`, sends out notices like weather alerts, capacity warnings and evacuation instructions, and every area that is registered to lists reacts in it's own way without `EventControl` ever needing to know what concrete type of object it is talking to. 

# Implementation of the 2 Design Patterns
- **Composite** answers "what is inside this part of the event?" and this is managed by `EventComponent`(the shared interface), `EventUnit` and it's 5 leaf types (`Stage`, `Booth` , `InfoDesk` , `Vendor`, `StaffTeam`), and `EvntGroup`(the composite that owns a tree of children).

- **Observer** answers "who needs to hear about this change?" which is implemented by the following,  `Subject`, `Observer`, `Notice`, `EventControl` as the ConcreteSubject at the top of the tree. `EventGroup` plays both a Subject role, to its own children, and an Observer role, to whatever is above it. 

All questions and more details are found in the PDF

## Builiding
Requires a C++11 compiler and `make`.

```bash
make          
./eventflow   
make clean    
```

The Makefile produces an executable named `eventflow`, built with
`-std=c++11 -Wall`, with zero warnings.

## What is the Result of Main and What is happening

`main.cpp` builds the full TechWave Expo tree, then walks through every
required behaviour in order:

1. Builds the Composite ownership tree (root -> halls/zones/corners ->
   leaves) and registers the top level areas as Observers of
   `EventControl`.
2. Opens the whole event with one call on the root (Composite
   traversal).
3. Prints a full status report (another Composite traversal).
4. Issues a `SCHEDULE_CHANGE` notice.
5. Issues a `CAPACITY_ALERT`, showing a busy booth suspend service while
   a quiet booth stays open (condition-based reaction).
6. Issues a `WEATHER_ALERT`, cascading through four runtime levels, with
   indoor and outdoor units reacting differently.
7. Detaches, then reattaches, an area at runtime (registration change).
8. Transfers a booth from one area to another while the program is
   running (Composite ownership + Observer registration both updated).
9. Issues `EVACUATE` then `RESUME`, showing a staff team becoming more
   active instead of shutting down.
10. Shuts down cleanly: detaches every top level observer from
    `EventControl`, then deletes the root of the Composite tree, which
    releases the entire owned subtree exactly once.

## Documentation

Public classes and operations are documented with Doxygen comments.
Generate browsable HTML docs with:

```bash
doxygen Doxyfile
```

## GitHub workflow
Our team used GitHub to work together on the project using a development branch. Team members added and updated their code on the development branch instead of working directly on the main branch. We used pull requests when changes needed to be reviewed and merged. WE committed our code regularly after completing a feature, fixing errors, or making changes as well when we done with a header or cpp file, rather than committing after every small change.