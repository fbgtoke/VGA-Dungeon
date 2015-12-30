#ifndef EVENTHISTORY_HPP
#define EVENTHISTORY_HPP

#include "utils.hpp"

enum DungeonEventType { DEFAULT, CIDLE, CMOVE, CATTACK, CDIED, CSPAWN, NEWTURN, NUMBEREVENTS };
struct DungeonEvent
{
    DungeonEventType type = DEFAULT;
    int ownerID = -1;
    int turn_number = -1;
    DungeonEvent() : type(DEFAULT), ownerID(-1), turn_number(-1) {};
    DungeonEvent(DungeonEventType e, int i, int t) : type(e), ownerID(i), turn_number(t) {};
};

class EventHistory
{
private:
    static const int MAXSIZE = 120;
    std::list<DungeonEvent> events;

    int turn;
    std::string msg[NUMBEREVENTS] = {"does nothing", "moves", "attacks!", "dies", "storms into battle", "NEW TURN!"};

public:
    EventHistory();
    ~EventHistory();

    void pushEvent(DungeonEventType event, int owner);

    std::list<DungeonEvent>::const_iterator getAllEvents() const;
    void getLastEvent(DungeonEvent& e) const;
    std::list<DungeonEvent>::const_iterator getLastEvents(int amount) const;

    void getLastEventFrom(int owner, DungeonEvent& e) const;
    void getEventsFrom(int owner, std::list<DungeonEvent>& l) const;

    void undoLastEvent();

    int getSize() const;
    int getCurrentTurn() const;
    void getEvent(int index, DungeonEvent& e) const;

    void printEvent(int index) const;
    void printAllEvents() const;
};

#endif // EVENTHISTORY_HPP
