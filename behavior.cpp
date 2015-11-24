#include "behavior.hpp"

Behavior::Behavior(int id, const CharacterFactory& f) : myid(id), factory(f) {}
Behavior::~Behavior() {}

int Behavior::getID() const { return myid; }
matrix<Tile>& Behavior::getView() { return view; }
    
Command Behavior::getCommand()
{
    Command c;
    c.setType(MOVE);

    int i = rand()%4;
    CommandDirection d[4] = {UP, DOWN, LEFT, RIGHT};
    c.setDirection(d[i]);

    return c;
}

