#include "behavior.hpp"

Behavior::Behavior(int id, const CharacterFactory& f) : myid(id), factory(f) {}
Behavior::~Behavior() {}

int Behavior::getID() const { return myid; }
matrix<Tile>& Behavior::getView() { return view; }
    
Command Behavior::getCommand() { return Command::DEFAULT; }

