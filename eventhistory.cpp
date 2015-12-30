#include "eventhistory.hpp"

EventHistory::EventHistory() { turn = 0; }
EventHistory::~EventHistory() {}

void EventHistory::pushEvent(DungeonEventType event, int owner)
{
    events.push_back(DungeonEvent(event, owner, turn));
    if (event == NEWTURN) ++turn;
}

std::list<DungeonEvent>::const_iterator EventHistory::getAllEvents() const { return events.cbegin(); }
void EventHistory::getLastEvent(DungeonEvent& e) const { if (events.size() > 0) e = events.back(); }
std::list<DungeonEvent>::const_iterator EventHistory::getLastEvents(int amount) const
{
    int n = amount;
    int size = events.size();
    if (n > size) n = events.size();
    std::list<DungeonEvent>::const_iterator it = events.cend();
    while (n > 0) { --it; --n; }
    return it;
}

void EventHistory::getLastEventFrom(int owner, DungeonEvent& e) const
{
    std::list<DungeonEvent>::const_iterator it = events.cend();
    while (it != events.begin())
    {
        if (it->ownerID == owner)
        {
            e = *it;
            return;
        }
        --it;
    }
}
void EventHistory::getEventsFrom(int owner, std::list<DungeonEvent>& l) const
{
    for (auto e : events)
    {
        if (e.ownerID == owner) l.push_back(e);
    }
}

void EventHistory::undoLastEvent()
{
    if (events.size() == 0) return;
    if (events.back().type == NEWTURN) --turn;
    events.pop_back();
}

int EventHistory::getSize() const { return events.size(); }
int EventHistory::getCurrentTurn() const { return turn; }
void EventHistory::getEvent(int index, DungeonEvent& e) const
{
    int size = events.size();
    if (index < size)
    {
        auto it = events.begin();
        while (index > 0) { ++it; --index; }
        e = *it;
    }
}

void EventHistory::printEvent(int index) const
{
    int size = events.size();
    if (index < size)
    {
        DungeonEvent aux;
        getEvent(index, aux);

        std::cout << "Event #" << index << ": ";
        std::cout << msg[aux.type]
                  << " by " << aux.ownerID
                  << " on turn " << aux.turn_number << std::endl;
    }
}
void EventHistory::printAllEvents() const
{
    int size = events.size();
    std::cout << "Printing " << size << " events" << std::endl;
    for (int i = 0; i < size; ++i)
    {
        printEvent(i);
    }
}

